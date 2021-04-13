#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 200001
#define M 500001
int n, m, visited[N];
vector<int> graf[N];
int ans[N];
bool czyMozna = 1;

void wej() {
	cin>>n>>m;
	rep(i,1,m) {
		int a, b;
		cin>>a>>b;
		graf[a].pb(b);
		graf[b].pb(a);
	}
}

void dfs(int v, int value) {
	value = (value + 1) % 2;
	ans[v] = value;
	visited[v] = 1; 
	for(auto u: graf[v])
		if(visited[u] == 0)
			dfs(u, value);
}

void solve() {
	rep(i,1,n)
		if(graf[i].size() == 0)
			czyMozna = 0;
	if(!czyMozna) {
		cout<<"NIE\n";
		return;
	}
	rep(i,1,n)
		if(visited[i] == 0)
			dfs(i, 0);
	cout<<"TAK\n";
	rep(i,1,n)
		if(ans[i])
			cout<<"K\n";
		else
			cout<<"S\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	solve();
	return 0;
}
