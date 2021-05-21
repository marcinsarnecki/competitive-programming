#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 50001
#define log 18

int n, c[N], t[N], k[N];
vector<int> graf[N], pytania[N];

int preorder[N], postorder[N], ldx, lca[log][N], odl[N];
int suma[N], currentK;

int ans[N];

void dfs1(int v, int p) {
	preorder[v] = ldx++;
	odl[v] = odl[p] + 1;
	lca[0][v] = p;
	for(auto u: graf[v])
		if(u != p)
			dfs1(u,v);
	postorder[v] = ldx++;
}

bool przodek(int v, int u) { //czy v jest przodkiem u
	return preorder[v] <= preorder[u] && postorder[v] >= postorder[u];
}

int getlca(int v, int u) {
	if(przodek(v,u)) return v;
	if(przodek(u,v)) return u;
	for(int i = log - 1; i >= 0; i--) 
		if(!przodek(lca[i][v],u)) 
			v = lca[i][v];
	return lca[0][v];
}

int skok(int v, int d) {
	for(int i = 0; i < log; i++) 
		if(d & (1<<i))
			v = lca[i][v];
	return v;
}

int odleglosc(int v, int u) {
	return odl[v] + odl[u] - (odl[getlca(v,u)] << 1);
}

int zbieraj(int v, int cel, int d) { //suma od ['v' do 'cel'), co 'd' 
	int wynik = 0;
	while(!przodek(v,cel)) {
		wynik += c[v];
		v = skok(v, d);
	}
	return wynik;
}

void wczytaj() {
	cin>>n;
	rep(i,1,n)
		cin>>c[i];
	rep(i,1,n-1) {
		int a, b;
		cin>>a>>b;
		graf[a].pb(b);
		graf[b].pb(a);
	}
	rep(i,1,n)
		cin>>t[i];
	rep(i,1,n-1)
		cin>>k[i];
}

void init() {//budowa lca
	dfs1(1,1);
	for(int i = 1; i < log; i++)
		for(int v = 1; v <= n; v++)
			lca[i][v] = lca[i-1][lca[i-1][v]];
}

void dfs2(int v, int p) {
	suma[v] = suma[skok(v,currentK)] + c[v];
	for(auto u: graf[v])
		if(u != p)
			dfs2(u,v);
	for(auto nr: pytania[v]) {
		int d = odleglosc(v, getlca(t[nr], t[nr+1]));
		if(d % currentK != 0) 
			d = (d + currentK) / currentK * currentK;//pierwsza liczba >= d podzielnia przez k
		ans[nr] += suma[v] - suma[skok(v,d)];
	}
}

void solve() {
	for(int i = 1; i * i < n; i++) {//przetworzenie malych zapytan
		currentK = i;
		rep(j,1,n) {
			suma[j] = 0;
			pytania[j].clear();
		}
		rep(j,1,n-1)
			if(k[j] == currentK)
				pytania[t[j]].pb(j), pytania[t[j+1]].pb(j);//zapisujemy w wierzcholkach numery pytan ktore ich dotycza, pozniej na nich dodajemy do danej odpowiedzi sume prefiksowa od tego wierzcholka do lca z zapytania
		dfs2(1,1);
	}
	rep(i,1,n-1) 
		if(!ans[i]) {//dla reszty zapytan (czyli dla k >= pierwiastek) skakanie co k
			int v = t[i], u = t[i+1];
			int cel = getlca(v, u);
			ans[i] += zbieraj(v, cel, k[i]);
			ans[i] += zbieraj(u, cel, k[i]);
		}
	rep(i,1,n-1) {//wszystkie dotychczasowe metody byly [v,lca), jesli dystans jest podzielny przez k to lca tez trzeba uwzglednic
		int v = t[i], u = t[i+1];
		int cel = getlca(v, u);
		if(odleglosc(v,cel) % k[i] == 0)
			ans[i] += c[cel];
	}
	rep(i,1,n-1)
		cout<<ans[i]<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	return 0;
}
