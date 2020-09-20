#include<bits/stdc++.h>
#define N 500005
using namespace std;
vector<int> graf[N];
int parent[N], ans = 1, n, q, strajk[N], children[N];//wolne dzieci

void dfs(int v, int p)
{
	parent[v] = p;
	for(auto u: graf[v]) if(u != p) dfs(u, v);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i < n; i++) {
		int v, u;
		cin>>v>>u;
		graf[v].push_back(u);
		graf[u].push_back(v);
	}
	dfs(1,1);
	children[1] = graf[1].size();
	for(int i = 2; i <= n; i++) children[i] = graf[i].size() - 1;
	cin>>q;
	for(int i = 1; i <= q; i++) {
		int v;
		cin>>v;
		if(v > 0)//strajk
		{
			strajk[v] = 1;
			int a = children[v];//wolni sasiedzi
			if(v != 1 && strajk[parent[v]] == 0) a++;
			if(v != 1) children[parent[v]]--;
			ans += a - 1;
			cout<<ans<<"\n"; 
		}
		else//odblokowanie miasta
		{
			v *= -1;
			strajk[v] = 0;
			int a = children[v];//wolni sasiedzi
			if(v != 1 && strajk[parent[v]] == 0) a++;
			if(v != 1) children[parent[v]]++;
			ans -= a - 1;
			cout<<ans<<"\n";
		}
	}
	return 0;
}
