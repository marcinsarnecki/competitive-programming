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
int n, m, visited[N], idx;
vector<int> graf[N], GT[N], skladowe[N], order;

void dfs1(int v)//postorder
{
	visited[v] = 1;
	for(auto u: graf[v]) if(!visited[u]) dfs1(u);
	order.push_back(v);
}

void dfs2(int v) {
	visited[v] = 1;
	skladowe[idx].pb(v);
	for(auto u: GT[v])
		if(visited[u] == 0)
			dfs2(u);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,m) {
		int v, u;
		cin>>v>>u;
		graf[v].pb(u);
		GT[u].pb(v);
	}
	rep(i,1,n) if(visited[i] == 0) dfs1(i);
	rep(i,1,n) visited[i] = 0;
	for(int i = order.size() - 1; i >= 0; i--) {
		if(visited[order[i]] == 0) {
			idx++;
			dfs2(order[i]);
		}
	}
	rep(i,1,idx) {	//wyswietlenie wszystkich silnie spojnych skladowych w grafie
		cout<<"Skladowa nr "<<i<<": ";
		for(auto v: skladowe[i]) cout<<v<<" ";
		cout<<"\n";
	}
	return 0;
}
