#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
#define N 1000005
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

vector<pii> graf[N];
vector<int> G[N], GT[N], order;
pii kr[N];
int dir[N];
int n, m, visited[N], sdx;

void dfs0(int v) {
	visited[v] = 1;
	for(auto it: graf[v]) {
		int nr = it.s;
		if(dir[nr] == 0) {
			if(v == kr[nr].f)
				dir[nr] = 1;
			else
				dir[nr] = 2;
			if(visited[it.f] == 0)
				dfs0(it.f);
		}
	}
}

void kierunki() {
	rep(v,1,n)
		if(visited[v] == 0) dfs0(v);
}

void dfs1(int v) {
	visited[v] = 1;
	for(auto u: G[v])
		if(visited[u] == 0) 
			dfs1(u);
	order.pb(v);
}

void dfs2(int v) {
	visited[v] = 1;
	for(auto u: GT[v])
		if(visited[u] == 0)
			dfs2(u);
}

void scc() {
	rep(i,1,n)
		visited[i] = 0;
	rep(i,1,m) {
		int v = kr[i].f, u = kr[i].s;
		if(dir[i] == 1) {
			G[v].pb(u);
			GT[u].pb(v);
		}
		if(dir[i] == 2) {
			G[u].pb(v);
			GT[v].pb(u);
		}
	}
	rep(v,1,n)
		if(visited[v] == 0)
			dfs1(v);
	rep(v,1,n)
		visited[v] = 0;
	repv(i,n-1,0) {
		int v = order[i];
		if(visited[v] == 0) {
			sdx++;
			dfs2(v);
		}
	}
}

void wczytaj() {
	cin>>n>>m;
	rep(i,1,m) {
		int v, u;
		cin>>v>>u;
		graf[v].pb({u,i});
		graf[u].pb({v,i});
		kr[i] = {v,u};
	}
}

void wypisz() {
	cout<<sdx<<"\n";
	rep(i,1,m)
		if(dir[i] == 1)
			cout<<">";
		else cout<<"<";
}
int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	kierunki();
	scc();
	wypisz();
	return 0;
}
