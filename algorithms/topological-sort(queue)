#include<bits/stdc++.h>
#define N 1000
using namespace std;

queue<int> Q;
vector<int> graf[N];
int InDegree[N];
int n,m;

int main()
{
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		int a,b;
		cin>>a>>b;
		graf[a].push_back(b);
		InDegree[b]++;
	}
	
	for(int i = 1; i <= n; i++)
		if(InDegree[i] == 0) Q.push(i);
	
	
	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		cout<<v<<" ";
		for(int i = 0; i < graf[v].size(); i++) {
			InDegree[graf[v][i]]--;
			if(InDegree[graf[v][i]] == 0) Q.push(graf[v][i]);
		}
	}
	return 0;
}
