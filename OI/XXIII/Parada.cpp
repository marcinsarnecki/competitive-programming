#include<bits/stdc++.h> // k * (suma dlugosci tras)
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 200001

int n, ans, dp[N];//najwiekszy wynik dla sciezki zaczynajacej sie w danym wierzcholku, sciezka idzie w poddrzewo
vector<int> graf[N];

void dfs(int v, int p) {
	for(auto u: graf[v])
		if(u != p)
			dfs(u,v);
	dp[v] = 0;
	int l = 0, best1 = -1, best2 = -1;//ile synow, dwa najlepsze dp wsrod synow
	for(auto u: graf[v])
		if(u != p) {
			l++;
			if(dp[u] > best1) {
				best2 = best1;
				best1 = dp[u];
			}
			else if(dp[u] > best2) 
				best2 = dp[u];
		}
	if(best1 != -1 && best2 == -1) { //tylko jeden syn
		ans = max(ans, best1 + (v != 1));//probujemy polepszyc wynik o dp syna, + 1 jesli nie jestesmy korzeniem 
		dp[v] = max(1, best1);
	}
	if(best1 != -1 && best2 != -1) { //mozemy skorzystac z dwoch synow
		ans = max(ans, best1 + l - 1 + (v != 1));//najlepsze dp, konczymy w v
		ans = max(ans, best1 + best2 + l - 2 + (v != 1));//dwa najlepsze dp + reszta wierzcholkow v
		dp[v] = max(best1 + l - 1, l);//do dp bierzemy albo best1 i reszta, albo l
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n-1) {
		int a, b;
		cin>>a>>b;
		graf[a].pb(b);
		graf[b].pb(a);
	}
	dfs(1,1);
	cout<<ans;
	return 0;
}
