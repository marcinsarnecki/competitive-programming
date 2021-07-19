#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int INF = 1e9;

#define B 1015

vector<ll> dp(B+1,INF);// dp[i] = k(i);
ll n;
ll u, m;//pierwsza sigma(m) >= n

ll bad;//dla ilu liczb nie ma rozwiazania (wszystkie z nich sa <= 128)

void init() {
	vector<ll> sq;
	rep(i,1,40)
		sq.pb(i*i);
	dp[0] = 0;
	for(auto x: sq)
		repv(i,B,x)
			dp[i] = min(dp[i], max(dp[i-x],x));
	rep(i,1,B)
		if(dp[i] != INF)
			dp[i] = sqrt(dp[i]);
	rep(i,1,128)
		if(dp[i] == INF)
			bad++;
	while(u < n) {
		m++;
		u += m * m;
	}
}

void solve() {
	if(n <= 1015) {//brut
		ll ans = dp[n], ile = 0;
		ll mini = m;
		repv(i,n,1) {
			if(dp[i] > mini)
				ile++;
			mini = min(mini, dp[i]);
		}
		if(ans == INF)
			cout<<"- "<<ile<<"\n";
		else
			cout<<ans<<" "<<ile<<"\n";
	}
	else {
		ll ans = m, ile = 0;
		ll mini = 14;
		repv(i,1015,1) {//ile liczb do 1015 (sigma(14))
			if(dp[i] > mini)
				ile++;
			mini = min(mini, dp[i]);
		}
		ile += bad * (m-15);//zbiorczo ile na pewno jest pomiedzy 1015 i n
		ll diff = u - n;
		if(diff <= 128) {//jesli jestesmy blisko nastepnej sigmy to trzeba recznie sprawdzic
			rep(i,diff,128)
				if(dp[i] == INF)
					ile++;
			if(dp[diff] == 	INF)
				ans++;
		}
		cout<<ans<<" "<<ile<<"\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	init();
	solve();
	return 0;
}
