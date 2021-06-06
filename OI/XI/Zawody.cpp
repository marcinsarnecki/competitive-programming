#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define INF 2000000000
#define N 5001

vector<pii> graf[N], graf2[N];
pii kraw[N * 2], kraw2[N * 2];//wagi danej krawedzi, wierzcholki 
int n, m, odl1[N], odl2[N];//odleglosc do v od startu, i na odwrot z v do startu w odrwoconym grafie w danych skladowych grafu
priority_queue<pii> Q;
int poprzednik[N];//poprzednik w pierwszej dijkstrze
vector<int> wychodzace[N];//krawedzie w skladowych (tylko wychodzace od startu w glab grafu)
int skladowa[N], idx, kd[N];//skladowe to odgalezienia drzewa najkrotszych sciezek wychodzacego ze startu, kd - odleglosci w krawedziach w skladowej
int ans = INF;

void dfs(int v, int d) {
	skladowa[v] = idx;
	kd[v] = d;
	for(auto u: wychodzace[v])
		dfs(u, d+1);
}

void wczytaj() {
	cin>>n>>m;
	rep(i,1,m) {
		int a, b, c, d;
		cin>>a>>b>>c>>d;
		graf[a].pb({b,c});
		graf[b].pb({a,d});
		kraw[i] = {c,d};
		kraw2[i] = {a,b};
		graf2[b].pb({a,c});
		graf2[a].pb({b,d});
	}
}

void solve() {
	rep(i,1,n) 
		odl1[i] = odl2[i] = INF;
	odl1[1] = odl2[1] = 0;
	Q.push({0,1});
	while(Q.size()) {//zwykla dijkstra
		int v = Q.top().s, d = Q.top().f * (-1);
		Q.pop();
		if(odl1[v] < d)
			continue;
		for(auto it: graf[v]) {
			int u = it.f, w = it.s;
			if(odl1[u] > d + w) {
				odl1[u] = d + w;
				poprzednik[u] = v;
				Q.push({-odl1[u], u});
			}
		}
	}
	rep(i,2,n) 
		wychodzace[poprzednik[i]].pb(i);//tworzymy krawedzie w skladowych
	for(auto u: wychodzace[1]) {//tworzymy skladowe
		dfs(u,1);
		idx++;
	}
	Q.push({0,1});
	while(Q.size()) {//dijkstra na odwroconym grafie chodzoca po skladowych, nie mozemy chodzic pomiedzy nimi
		int v = Q.top().s, d = Q.top().f * (-1);
		Q.pop();
		if(odl2[v] < d)
			continue;
		for(auto it: graf2[v]) {
			int u = it.f, w = it.s;
			if(odl2[u] > d + w && (v == 1 || skladowa[v] == skladowa[u])) {//mozemy isc tylko po tych samych skladowych, wyjatkiem jest pierwszy wierzcholek, bez tego || ta dijkstra by nie wystartowala do reszty skladowych
				odl2[u] = d + w;
				Q.push({-odl2[u], u});
			}
		}
	}
	rep(i,1,m) {
		int v = kraw2[i].f, u = kraw2[i].s;
		int w1 = kraw[i].f, w2 = kraw[i].s;//w dwa kierunki
		if(v != 1 && u != 1 && skladowa[v] != skladowa[u]) {//krawedz pomiedzy skladowymi (bez startowego wierzcholka), mozemy normalnie brac wynik
			ans = min(ans, odl1[v] + w1 + odl2[u]);
			ans = min(ans, odl1[u] + w2 + odl2[v]);
		}
		else {//w obrebie jednej skladowej mozemy brac wynik ale potrzebujemy warunku kd >= 2
			if(u == 1 && kd[v] >= 2) 
				ans = min(ans, w1 + odl1[v]);	
			if(v == 1 && kd[u] >= 2) 
				ans = min(ans, w2 + odl1[u]);
		}
	}
	cout<<ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
