#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000001

struct point{
	int d, t, id;//odleglosc, poczatek 0 koniec 1, ktory prawnik
};

int n, k, ans, where, aktywni, kty, pom[N];
pii prawnicy[N];
vector<point> points;
bool active[N];

bool compare(const point& A, const point& B) {
	if(A.d == B.d)
		return A.t > B.t;//najpierw konce, potem poczatki w tej samej odleglosci
	return A.d < B.d;//po odleglosci
}

void wczytaj() {
	cin>>n>>k;
	rep(i,1,n) {
		int a, b;
		cin>>a>>b;
		prawnicy[i] = {a,b};
		points.pb({a,0,i});
		points.pb({b,1,i});
	}
}

void solve() {
	sort(points.begin(), points.end(), compare);
	rep(i,0,2*n-1)
		if(points[i].t == 0) //kazdy prawnik pamieta indeks swojego poczatkowego punktu, potrzebne przy przesuwaniu k'tego prawnika
			pom[points[i].id] = i;
	rep(i,0,2*n-1) {
		if(points[i].t == 0) {//trafilismy na poczatek
			active[points[i].id] = 1;
			if(++aktywni == k)//jesli po uwzglednieniu tego poczatku liczba aktywnych prawnikow jest rowna k, to zaznaczamy gdzie zaczyna sie k'ty prawnik
				kty = i;
		}
		else { //trafilismy na koniec
			active[points[i].id] = 0;
			if(aktywni >= k) {//jesli jest wystarczajaco duzo prawnikow to probujemy polepszyc wynik
				if(points[i].d - points[kty].d > ans) {
					ans = points[i].d - points[kty].d;
					where = points[i].d;
				}
			}
			if(--aktywni >= k && kty >= pom[points[i].id]) {//jesli poczatek prawnika ktory sie wlasnie skonczyl znajduje sie przed poczatkiem k'tego prawnika
				kty++;										// to musimy zaktualizowac pozycje k'tego prawnika, bo w tym momencie wskazuje ona na (k-1)'tego prawnika 
				while(!active[points[kty].id]) //idziemy do przodu dopoki nie trafimy na poczatek jakiegos prawnika
					kty++;
			}
		}
	}
	cout<<ans<<"\n";
	int i = 1, a = where - ans, b = where;
	while(k > 0) {//majac miejsce i dlugosc wynikowego przedzialu wystarczy wybrac dowolne k prawnikow pokrywajacych ten przedzial
		if(prawnicy[i].f <= a && prawnicy[i].s >= b) {
			cout<<i<<" ";
			k--;
		}
		i++;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
