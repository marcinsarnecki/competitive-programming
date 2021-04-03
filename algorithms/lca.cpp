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

#define N 1001
#define log 18
vector<int> graf[N];
int preorder[N], postorder[N], ldx, lca[log][N], n;

void dfs(int v, int p) {
	lca[0][v] = p;
	preorder[v] = ++ldx;
	for(auto u: graf[v])
		if(u != p)
			dfs(u, v);
	postorder[v] = ++ldx;
}

bool przodek(int v, int u) { //czy v jest przodkiem u
	if(v == u)
		return true;
	if(preorder[v] < preorder[u] && postorder[v] > postorder[u]) 
		return true;
	return false;
}

int getlca(int v, int u) {
	if(przodek(v,u)) return v;//to important
	if(przodek(u,v)) return u;
	for(int i = log - 1; i >= 0; i--) //wystarczy skakac potegami 2
		if(!przodek(lca[i][v],u)) 
			v = lca[i][v];
	return lca[0][v];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n-1) {
		int v, u;
		cin>>v>>u;
		graf[v].pb(u);
		graf[u].pb(v);
	}
	dfs(1,1);
	for(int i = 1; i < log; i++)
		for(int v = 1; v <= n; v++)
			lca[i][v] = lca[i-1][lca[i-1][v]];
	//od teraz getlca(v,u) zwraca wierzcholek, ktory jest lca dla v,u
	return 0;
}
