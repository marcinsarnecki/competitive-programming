#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 150001
int n, k, tab[N], visited[4*N], nr[4*N], sdx;
vector<int> graf[4*N], graf2[4*N], order; // scc
unordered_map<ll, int> m;// hash pary kolejnych liczb -> ich ostatnie wystapienie

inline ll pair_value(int a1, int a2) { return (ll)a1*(n+1)+a2; } //proste hashowanie pary dwoch kolejnych liczb z wejscia
inline int x(int i) { return 2*i; }; // kazdy x potrzebuje 2 wierzcholkow: x oraz negacje x (zakres <1, 2n>)
inline int p(int i) { return 2*n + x(i); }; // dodatkowe wierzcholki do prefiksowych or
inline int neg(int i) { return ((i & 1) == 1) ? i+1 : i-1; }; //negacja danego wierzcholka

void add_alternative(int a, int b) { // dodanie kolejnej klauzuli do 2sata
	graf[neg(a)].pb(b);// a or b === (not a -> b and not b => a)
	graf[neg(b)].pb(a);
	graf2[b].pb(neg(a)); 
	graf2[a].pb(neg(b));
}

void clear_all() {
	m.clear();
	order.clear();
	sdx = 0;
	rep(i,1,4*n) {
		visited[i] = nr[i] = 0;
		graf[i].clear();
		graf2[i].clear();
	}
}

void dfs1(int v) { //dfsy do scc
	visited[v] = 1;
	for(auto u: graf[v])
		if(!visited[u])
			dfs1(u);
	order.pb(v);
}

void dfs2(int v) {
	visited[v] = 1;
	nr[v] = sdx;
	for(auto u: graf2[v])
		if(!visited[u])
			dfs2(u);
}


bool check_2sat() {
	rep(i,1,4*n) // standard scc
		if(!visited[i])
			dfs1(i);
	rep(i,1,4*n)
		visited[i] = 0;
	for(int i = (int)order.size() - 1; i >= 0; i--) {
		int v = order[i];
		if(!visited[v]) {
			++sdx;
			dfs2(v);
		}
	}
	for(int i = 1; i <= 4 * n; i+=2) 
		if(nr[i] == nr[neg(i)]) // rozwiazanie nie istnieje jesli istnieje cykl zawierajacy x oraz negacje x
			return false;
	return true;
}

void solve() {
	cin>>n>>k;
	rep(i,1,n)
		cin>>tab[i];
	add_alternative(x(1), x(1));// na pewno trzeba zamalowac pozycje 1 oraz n-1
	add_alternative(x(n-1), x(n-1));
	rep(i,1,n-2)
		add_alternative(x(i), x(i+1)); //na pewno jedna z kazdych dwoch kolejnych
	rep(i,1,n-1) { //jesli para wystepuje wiele razy to tylko raz mozna jej uzyc, trzeba to rozwiazac
		ll val = pair_value(tab[i], tab[i+1]);
		if(m.count(val) == 0) { //pierwsze wystapienie, poczatek zbioru w ktorym tylko jeden x moze byc prawdziwy
			m[val] = i;
			add_alternative(neg(x(i)), p(i));//rownowaznosc pomiedzy pierwszym wystapieniem i pierwszym orem prefiksowym
			add_alternative(x(i), neg(p(i)));
		}
		else { //kolejne wystapienie
			int prev = m[val];//wystarczy pododawac implikacje w prawa strone na orach preifksowych oraz implikacje w gore na kazdym miejscu
			m[val] = i;//oraz not and na przekatnej pomiedzy wystapieniem x oraz poprzednim orem prefiksowym
			add_alternative(neg(x(i)), neg(p(prev)));//not and przekatna na przekatnej
			add_alternative(neg(p(prev)), p(i));//ciag implikacji prefiksow
			add_alternative(neg(x(i)), p(i));//wystapienie x implikuje prawde na danym orze przefiksowym
		}
	}
	cout<< (check_2sat() ? "TAK\n" : "NIE\n");
}



int main() {
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) {
		solve();
		clear_all();
	}
	return 0;
}
