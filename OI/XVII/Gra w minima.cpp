#include<bits/stdc++.h>
using namespace std;
int tab[1000001],n,dp[1000001];
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>tab[i];
	sort(tab+1,tab+1+n);
	dp[1] = tab[1];
	for(int i = 2; i <= n; i++) dp[i] = max(dp[i-1], tab[i] - dp[i-1]);
	cout<<dp[n];
	return 0;

