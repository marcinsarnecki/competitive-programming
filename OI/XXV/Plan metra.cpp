#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 1000001

int n, odl1[N], odl2[N];//odleglosci od 1 i n

bool brzeg = 1;
int dbrzeg;

vector<int> nr;//same numery wierzcholkow na sciezce
int d;
int sciezka[2*N];// indeksem jest odleglosc od 1, wartoscia nunmer wierzcholka
vector<pii> graf[2*N];//krawedzie postaci <nr,waga>

void wczytaj() {
	cin>>n;
	rep(i,2,n-1) cin>>odl1[i];
	rep(i,2,n-1) cin>>odl2[i];
}

void solve() {
	if(n == 1) {
		cout<<"TAK\n";
		return;
	}
	if(n == 2) {
		cout<<"TAK\n";
		cout<<"1 2 1\n";
		return;
	}
	//case 1: przypadek brzegowy, wszystkie roznice takie same
	dbrzeg = abs(odl1[2] - odl2[2]);
	rep(i,3,n-1) 
		if(abs(odl1[i] - odl2[i]) != dbrzeg) brzeg = 0;
	if(dbrzeg == 0) brzeg = 0;//odleglosc od 1 do n nie moze byc rowna 0 nawet jesli wszystkie roznice sa takie same (np test 6 1 2 3 4 1 2 3 4)
	if(brzeg) {
		cout<<"TAK\n";
		cout<<"1 "<<n<<" "<<dbrzeg<<"\n";//krawedz 1 - n
		rep(i,2,n-1)
			if(odl1[i] > odl2[i]) cout<<n<<" "<<i<<" "<<odl2[i]<<"\n";
			else cout<<"1 "<<i<<" "<<odl1[i]<<"\n";
		return;
	}
	//case 2: wierzcholki o minimalnym odl1 + odl2 na sciezce 1 - n
	d = odl1[2] + odl2[2];
	rep(i,3,n-1)
		d = min(d, odl1[i] + odl2[i]);
	sciezka[0] = 1;
	sciezka[d] = n;
	rep(i,2,n-1)
		if(odl1[i] + odl2[i] == d) nr.pb(i);
	for(auto v: nr)
		if(sciezka[odl1[v]] == 0)
			sciezka[odl1[v]] = v;
		else {
			cout<<"NIE\n"; //dwa wierzcholki nie moga lezec w tym samym miejscu na sciezke pomiedzy 1 - n
			return;
		}
	rep(i,2,n-1) {
		if(odl1[i] + odl2[i] != d) {//wierzcholek nie lezacy na sciezce 1 - n
			if(abs(odl1[i] - odl2[i] == d)) //wierzcholek jest sasiadem 1 albo n
				if(odl1[i] > odl2[i]) 
					graf[d].pb({i,odl2[i]});
				else 
					graf[0].pb({i,odl1[i]});
			else { //wierzcholek musi byc odgalezieniem na sciezce 1 - n
				if(abs(odl1[i] - odl2[i] > d)) {
					cout<<"NIE\n";//roznica jest za duza, wierzcholek nie pasuje, NIE
					return;
				}
				int dif = odl1[i] - odl2[i];
				int pom = abs(dif);
				if(pom % 2 == d % 2) {//trzeba sprawdzic parzystosc, jesli jest inna to odleglosci wyszlyby z ulamkami 0.5
					int d1 = (dif+d) / 2;//odleglosc od 1 do wierzcholka na sciezce w ktorym bedzie odgalezienie do wierzcholka i
					if(sciezka[d1] == 0) {
						cout<<"NIE\n";//nie ma wierzcholka w tym miejscu, wiec sie nie da
						return;
					}
					else
						graf[d1].pb({i,odl1[i] - d1});
				}
				else {
					cout<<"NIE\n";
					return;
				}
			}
		}
	}
	cout<<"TAK\n";
	for(int i = 1, akt = 1, last = 1; i <= d; i++, akt++)  //akt - aktualna odleglosc od ostatniego wierzcholka, last - ostatnie wierzcholek
		if(sciezka[i] != 0) {
			cout<<last<<" "<<sciezka[i]<<" "<<akt<<"\n";
			last = sciezka[i];
			akt = 0;
		}
	//sciezka wypisana, teraz reszta wierzcholkow
	rep(i,0,d)
		for(auto it: graf[i])
			cout<<sciezka[i]<<" "<<it.f<<" "<<it.s<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
