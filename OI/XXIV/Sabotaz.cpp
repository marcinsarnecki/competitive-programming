#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 500001
int n, k, roz[N];
double morale[N], ans;
vector<int> graf[N];

void dfs(int v) {//dfs do rozmiarow 
	for(auto u: graf[v])
		dfs(u);
	roz[v] = 1;
	for(auto u: graf[v]) 
		roz[v] += roz[u];
}

void dfs2(int v) {//dfs do morali
	if(graf[v].size() == 0) { //lisc
		morale[v] = 1.0;
		return;
	}
	double m = 0.0;
	for(auto u: graf[v])
		dfs2(u);
	for(auto u: graf[v])
		m = max(m, min((double)roz[u] / (roz[v] - 1), morale[u]));
	morale[v] = m;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>k;
	rep(i,2,n) {
		int u;
		cin>>u;
		graf[u].pb(i);
	}
	dfs(1);
	dfs2(1);
	rep(i,1,n)
		if(roz[i] > k) 
			ans = max(ans, morale[i]);
	cout<<ans<<"\n";
	return 0;
}
