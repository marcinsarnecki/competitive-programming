#include<bits/stdc++.h>
using namespace std;
vector<int> graf[200001];
int u,wynik,a,b,n,dp[200001],ans[200001];

void dfs(int v,int p)
{
	for(auto u: graf[v]) if(u != p) dfs(u,v);
	int l = 0, b1 = 0, b2 = 0;
	for(auto u: graf[v])
	{
		if(u != p)
		{
			l++;
			if(dp[u] > b1)
			{
				b2 = b1;
				b1 = dp[u];
			}
			else if(dp[u] > b2)
			{
				b2 = dp[u];
			}
		}
	}
	dp[v] = max(l, l + b1 - 1);
	ans[v] = l + b1 -1;
	if(l >= 2) ans[v] = max(ans[v], b1 + b2 + l - 2);
	if(v != 1) ans[v]++;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i < n; i++)
	{
		cin>>a>>b;
		graf[a].push_back(b);
		graf[b].push_back(a);
	}

	dfs(1,0);
	for(int i = 1; i <= n; i++) wynik = max(wynik, ans[i]);
	cout<<wynik;
		
	
	return 0;
}
