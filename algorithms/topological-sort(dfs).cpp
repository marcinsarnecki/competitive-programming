#include<bits/stdc++.h>
#define N 1000
using namespace std;

vector<int> graf[N];
int visited[N];
int n,m;
list<int> l;

void dfs(int v)
{
	visited[v] = 1;
	for(int i = 0; i < graf[v].size(); i++)
		if(visited[graf[v][i]] == 0) dfs(graf[v][i]);
	l.push_front(v);
}

int main()
{
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		int a,b;
		cin>>a>>b;
		graf[a].push_back(b);
	}
	for(int i = 1; i <= n; i++) if(visited[i] == 0) dfs(i);
	for(auto it = l.begin(); it != l.end(); it++) cout<<*it<<" ";
	return 0;
}
