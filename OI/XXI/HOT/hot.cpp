#include<bits/stdc++.h>
#define f first
#define N 5001
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

int n;
vector<int> graf[N];

int idx;
ll Ans, vans[N];
vector<vector<int>> depth;
vector<int> all;//wszystkie na danej glebokosci

void wczytaj() {
	cin>>n;
	rep(i,1,n-1) {
		int v, u;
		cin>>v>>u;
		graf[v].pb(u);
		graf[u].pb(v);
	}
}

void dfs(int v, int p, int d) {
	if(d == (int)depth[idx].size())
		depth[idx].pb(1);
	else 
		depth[idx][d]++;
	for(auto u: graf[v])
		if(u != p)
			dfs(u,v,d+1);
}

void solve() {
	rep(v,1,n) {
		depth.clear();
		all.clear();
		idx = 0;
		for(auto u: graf[v]) {
			depth.pb(vector<int>());
			dfs(u,v,0);
			idx++;
		}
		rep(i,0,idx-1) {
			rep(j,0,(int)depth[i].size()-1) {
				if(j == (int)all.size())
					all.pb(0);
				all[j] += depth[i][j];
			}
		}
		for(auto it: all) {
			ll x = it;
			vans[v] += x * (x-1) * (x-2) / 6;//dodajemy wszystkie
		}
		rep(i,0,idx-1) {
			rep(j,0,(int)depth[i].size()-1) {
				ll rest = all[j] - depth[i][j], a = depth[i][j];
				vans[v] -= a * (a-1) * rest / 2;//odpowiedno odejmujemy
				vans[v] -= a * (a-1) * (a-2) / 6;
			}
		}
	}
	rep(v,1,n)
		Ans += vans[v];
	cout<<Ans<<"\n";
}



int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
