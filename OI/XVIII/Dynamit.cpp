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
#define N 300001

int Ans, n, m, t, curr, dp[2][N];// 0 - najglebszy niezapalony // 1 - najblizszy aktywny
vector<int> graf[N];
bool dyn[N];//czy jest tam dynamit

void dfs(int v, int p) {//t to potencjalny dobry czas
	for(auto u: graf[v])
		if(u != p)
			dfs(u, v);
	dp[1][v] = INF;
	if(dyn[v]) dp[0][v] = 0;
	else dp[0][v] = -1;//nie ma dynamitu;
	for(auto u: graf[v]) {
		if(u != p) {
			if(dp[0][u] != -1)
				dp[0][v] = max(dp[0][v], dp[0][u] + 1);
			dp[1][v] = min(dp[1][v], dp[1][u] + 1);
		}
	}
	int d = dp[0][v], a = dp[1][v]; 
	if(d == -1)
		return;
	if(v == 1) {
		if(d + a > t) 
			curr++;
		return;
	}
	if(d + a <= t) {
		dp[0][v] = -1;
		return;
	}
		
	if(t == d) {
		dp[1][v] = 0;
		dp[0][v] = -1;
		curr++;
	}
}


void wczytaj() {
	cin>>n>>m;
	rep(i,1,n) {
		int b;
		cin>>b;
		dyn[i] = b;
	}
	rep(i,1,n-1) {
		int v, u;
		cin>>v>>u;
		graf[v].pb(u);
		graf[u].pb(v);
	}
}

void binsearch() {
	int l = 0, r = n;
	while(l <= r) {
		t = (l + r) / 2;
		curr = 0;
		dfs(1,1);
		if(curr <= m) r = t - 1;
		else l = t + 1;
	}
	Ans = r + 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	binsearch();
	cout<<Ans;
	return 0;
}
