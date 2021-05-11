#include<bits/stdc++.h>
using namespace std;
int n,m,czerwone[1001];
long long wszystkie,rozne;
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++){
		int a,b;
		cin>>a>>b;
		czerwone[a]++;
		czerwone[b]++;
	}
	wszystkie = (long long) n * (n-1) * (n-2) / 6;
	for(int i = 1; i <= n; i++){
		rozne += (n - 1 - czerwone[i]) * czerwone[i];
	}
	rozne /= 2;
	cout<<wszystkie - rozne;
	return 0;
}
