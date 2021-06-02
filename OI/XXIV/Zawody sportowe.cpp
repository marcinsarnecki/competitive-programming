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

#define MOD 1000000007
#define N 1000001
int n;
vector<int> pozycje[N]; //vector z zawodnikami na danej pozycji
int zaw[N][2];		//krawedzie wychodzace z zawodnika
int ans[N], id[N];	//ans[i] to pozycja itego zawodnika, id[i] - numer zawodnika ktory jest na itej pozycji 
char z;
ll ile = 1;


void wczytaj() {
	cin>>n;
	rep(i,1,n) {
		cin>>z;
		int a;
		cin>>a;
		zaw[i][0] = a;
		pozycje[a].pb(i);
		if(z != 'T') {
			cin>>a;
			zaw[i][1] = a;
			pozycje[a].pb(i);
		}
	}
}

bool dfs(int v) {//szuka pewnikow //zwraca falsz jesli dane sa sprzeczne
	if(ans[v] != 0)
		return true;//jesli dany v jest juz obluzony to wychodzimy
	int pewnik = 0; 
	if(zaw[v][1] == 0)
		pewnik = zaw[v][0];//nie ma drugiej krawedzi, jest pewnosc
	else 
		for(int i = 0; i < 2; i++)  //szukamy pewnika w przypadku kiedy jedna z krawedzi prowadzi do zajetej pozycji 
			if(id[zaw[v][(i+1)%2]] != 0 || pozycje[zaw[v][i]].size() == 1) //albo jesli jakas pozycja ma tylko jedna krawedz
				pewnik = zaw[v][i];
	if(pewnik != 0) { //jesli znalezlismy pewnika (nie zawsze znajdziemy)
		if(id[pewnik] != 0) 
			return false; 	//mozemy trafic na sprzeczne dane 
		ans[v] = pewnik;	
		id[pewnik] = v;		//zaznaczamy to miejsce
		for(int u: zaw[v])	//musimy usunac krawedz ktorej v na pewno nie uzyje (dzieki temu byc moze inny v odnajadzie swojego pewnika)
			if(u != pewnik)
				for(int i = 0; i < (int)pozycje[u].size(); i++) //wywalamy z vectora
					if(pozycje[u][i] == v) {
						pozycje[u][i] = pozycje[u].back();
						pozycje[u].pop_back();
						break;
					}
		for(int u: zaw[v])
			for(int zawodnik: pozycje[u]) //wywloujemy sie rekurencyjnie
				if(!dfs(zawodnik))
					return false;	
	}
	return true;
}

void solve() {
	rep(i,1,n) 
		if(!dfs(i)) {//wstepne szukanie pewnikow
			cout<<"NIE\n";
			cout<<"0\n";
			return;
		}
	rep(i,1,n) 
		if(ans[i] == 0) { //jesli dane sa poprawne, to wierzcholki niepewne pogrupuja sie w skladowe;
			ile = (ile * 2) % MOD;//jedna decyzja spowoduje zdeterminowanie reszty odpowiedzi w skladowej, wiec mnozymy *2 ilosci
			zaw[i][1] = 0;//wiec usuwamy jedna krawedz i wywolujemy sie dfsem
			if(!dfs(i)) {//moze sie zdarzyc ze nasze dane sa jednak niepoprawne (bez tego kontrprzyklad 4 N 1 2 N 3 4 N 3 4 N 3 4)
				cout<<"NIE\n";
				cout<<"0\n";
				return;
			}
		}
	if(ile == 1) {//jesli jednoznacznie o wypisujemy wszystkie odpowiedzi
		cout<<"TAK\n";
		rep(i,1,n)
			cout<<ans[i]<<"\n";
	}
	else {
		cout<<"NIE\n";//a jak nie to wypisujemy na ile sposobow
		cout<<ile<<"\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
