#include<bits/stdc++.h>
#define N 50001
using namespace std;
vector<int> graf[N], GT[N], grafscc[N], order;
int visited[N], rozmiar[N], ans[N], nr[N], idx, n, m, In[N];
pair<int,int> kraw[2 * N];
queue<int> Q;

void dfs1(int v)
{
	visited[v] = 1;
	for(auto u: graf[v]) if(!visited[u]) dfs1(u);
	order.push_back(v);
}

void dfs2(int v)
{
	visited[v] = 1;
	nr[v] = idx;
	rozmiar[idx]++;
	for(auto u: GT[v]) if(!visited[u]) dfs2(u);
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		int v, u;
		cin>>v>>u;
		graf[v].push_back(u);
		GT[u].push_back(v);
		kraw[i] = {v,u};
	}
	for(int i = 1; i <= n; i++) if(!visited[i]) dfs1(i);
	for(int i = 1; i <= n; i++) visited[i] = 0;
	for(int i = order.size() - 1; i >= 0; i--) {
		if(!visited[order[i]]) {
			idx++;
			dfs2(order[i]);
		}
	}
	order.clear();
	for(int i = 1; i <= m; i++) {
		int v = kraw[i].first, u = kraw[i].second;
		if(nr[v] != nr[u]) {
			grafscc[nr[v]].push_back(nr[u]);
			In[nr[u]]++;
		}
	}
	for(int i = 1; i <= idx; i++) if(In[i] == 0) Q.push(i);
	
	while(Q.size()) {
		int v = Q.front();
		Q.pop();
		order.push_back(v);
		for(auto u: grafscc[v]) {
			In[u]--;
			if(In[u] == 0) Q.push(u);
		}
	}
	
	for(int i = order.size() - 1; i >= 0; i--) {
		int v = order[i];
		ans[v] = rozmiar[v] - 1;
		for(auto u: grafscc[v]) {
			ans[v] += ans[u] + 1;
		}
	}
	for(int i = 1; i <= n; i++) cout<<ans[nr[i]]<<"\n";
	return 0;
}
