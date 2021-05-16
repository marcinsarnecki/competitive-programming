#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 500001
#define M 1000001

vector<int> graf[N], graf2[N], graf3[N], graf4[N], order, topo;//normalny i odwrocony, scc + odwrocony 
int n, m, nr[N], idx, visited[N], topoid[N], ans;
pii kraw[M];
bool bad[N];

void wczytaj() {
	cin>>n>>m;
    rep(i,1,m) {
        int a, b;
        cin>>a>>b;
        kraw[i] = {a,b};
        graf[a].pb(b);
        graf2[b].pb(a);
    }
}

void dfs1(int v) {
	visited[v] = 1;
	for(auto u: graf[v]) if(!visited[u]) dfs1(u);
	order.push_back(v);
}

void dfs2(int v) {
	visited[v] = 1;
	nr[v] = idx;
	for(auto u: graf2[v]) if(!visited[u]) dfs2(u);
}

void dfs3(int v) {
    visited[v] = 1;
    for(auto u: graf3[v])
        if(!visited[u])
            dfs3(u);
    topo.pb(v);
}

void init() {
    rep(i,1,n)
        if(!visited[i])
            dfs1(i);
    rep(i,1,n) visited[i] = 0;
    repv(i,n-1,0) {
        int v = order[i];
        if(!visited[order[i]]) {
            dfs2(order[i]);
            idx++;
        }
    }
    rep(i,1,m) {
        int v = kraw[i].f, u = kraw[i].s;
        if(nr[v] != nr[u]) {
            graf3[nr[v]].pb(nr[u]);//grafy scc
            graf4[nr[u]].pb(nr[v]);
        }
    }
    rep(i,1,n) visited[i] = 0;
    rep(i,0,idx-1) {
        if(!visited[i]) 
            dfs3(i);
    }
    reverse(topo.begin(), topo.end());
    int pom = 0;
    for(auto it: topo) topoid[it] = pom++;
}

void solve() {
    int current = 0;
    for(int i = 0; i < topo.size(); i++) {
        if(i < current)
            bad[i] = 1;
        int r = n + 1;
        for(auto u: graf3[topo[i]])   
            r = min(r, topoid[u]);
        current = max(current, r);
    }
    current = topo.size() - 1;
    for(int i = topo.size() - 1; i >= 0; i--) {
        if(i > current)
            bad[i] = 1;
        int r = -1;
        for(auto u: graf4[topo[i]])
            r = max(r, topoid[u]);
        current = min(current, r);
    }
    rep(i,1,n)
        if(!bad[nr[i]])
            ans++;
    cout<<ans<<"\n";
    rep(i,1,n)
        if(!bad[nr[i]])
            cout<<i<<" ";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
    solve();
	return 0;
}
