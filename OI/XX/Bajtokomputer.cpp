#include<bits/stdc++.h>
#define N 1000001
#define INF 10000000
#define ujemny 0
#define zero 1
#define dodatni 2
using namespace std;
int n, ans, x[N], dp[N][3];//koszt uzyskania ciagu niemalejace dlugosci i konczacego sie na -1 0 1 
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>x[i];
	
	dp[1][0] = dp[1][1] = dp[1][2] = INF;//poczatkowa wartosc
	dp[1][x[1] + 1] = 0;
	
	for(int i = 2; i <= n; i++) {
		if(x[i] == -1) {
			dp[i][ujemny] = dp[i-1][ujemny];
			dp[i][zero] = INF;
			dp[i][dodatni] = dp[i-1][dodatni] + 2;
		}
		if(x[i] == 0) {
			dp[i][ujemny] = dp[i-1][ujemny] + 1;
			dp[i][zero] = min(dp[i-1][ujemny], dp[i-1][zero]);//izi
			dp[i][dodatni] = dp[i-1][dodatni] + 1;
		}
		if(x[i] == 1) {
			dp[i][ujemny] = dp[i-1][ujemny] + 2;
			dp[i][zero] = dp[i-1][ujemny] + 1;//izi
			dp[i][dodatni] = min(dp[i-1][ujemny], min(dp[i-1][zero], dp[i-1][dodatni]));
		}
	}
	ans = min(dp[n][ujemny], dp[n][zero]);
	ans = min(ans, dp[n][dodatni]);
	if(ans < INF) cout<<ans;//np dla przypadku 0 0 0 -1 odpowiedzia bedzie BRAK
	else cout<<"BRAK";
	return 0;
}
