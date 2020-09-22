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
int visited[N], n, m;
vector<int> graf[N];

void dfs(int v) {	//basic dfs
	visited[v] = 1;
	cout<<"odwiedzam wierzcholek "<<v<<"\n";
	for(auto u: graf[v]) 
		if(visited[u] == 0)
			dfs(u);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,m) {
		int v, u;
		cin>>v>>u;
		graf[v].pb(u);
		graf[u].pb(v);
	}
	dfs(1);
	return 0;
}
