#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define N 100001
#define log 18
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

vector<pii> graf[N]; //{u,waga}
int sq, n, r, ile[N];//ile[x] ile restauracji rodzaju x
vector<int> pozycje[N];//ita restauracja ma wszystkie swoje pozycje w pozycje[i]

int q;
pair<pii,int> zap[N];// f - wierzcholki, s - r

ll finalAns[N];
int done[N];

int preorder[N], postorder[N], ldx;//podstawowe lca
ll dist[N];
int lca[log][N];

ll dist2[N], lca2[log][N];//tymczasowe pomocnicze lca, ono trzyma minimum na skoku!!!
priority_queue<pair<ll,int>> Q;

void dfs1(int v, int p, ll d) {
	dist[v] = d;
	lca[0][v] = p;
	preorder[v] = ldx++;
	for(auto it: graf[v]) {
		if(it.f != p)
			dfs1(it.f, v, d + it.s);
	}
	postorder[v] = ldx++;
}

bool przodek(int v, int u) {
	if(v == u) return true;
	if(preorder[v] < preorder[u] && postorder[v] > postorder[u]) return true;
	return false;
}

int getlca(int v, int u) {
	if(przodek(v, u)) return v;
	if(przodek(u, v)) return u;
	int vv = v;
	repv(i,log-1,0)	if(!przodek(lca[i][vv],u)) vv = lca[i][vv];
	return lca[0][vv];
}

ll odl(int v, int u) {
	if(v == u)
		return 0;
	int x = getlca(v, u);
	return (ll)dist[v] + dist[u] - (2 * dist[x]);
}

ll speciallca(int v, int u) {//znajduje minimalna droge do jakies kolacji ze sciezki v -> u
	ll ans = INF;
	if(v == u) 
		return dist2[v];
	if(przodek(v,u)) {
		repv(i,log-1,0) if(!przodek(lca[i][u],v)) {
				ans = min(ans, lca2[i][u]);
				u = lca[i][u];
			}
		ans = min(ans, lca2[0][u]);
		return ans;
	}
	if(przodek(u,v)) {
		repv(i,log-1,0) if(!przodek(lca[i][v],u)) {
				ans = min(ans, lca2[i][v]);
				v = lca[i][v];
			}
		ans = min(ans, lca2[0][v]);
		return ans;
	}
	repv(i,log-1,0) if(!przodek(lca[i][v],u)) {
		ans = min(ans, lca2[i][v]);
		v = lca[i][v];
	}
	repv(i,log-1,0) if(!przodek(lca[i][u],v)) {
		ans = min(ans, lca2[i][u]);
		u = lca[i][u];
	}
	ans = min(ans, lca2[0][v]);
	ans = min(ans, lca2[0][u]);
	return ans;
}

void wczytaj() {
	cin>>n>>r;
	sq = sqrt(n);
	rep(v,1,n) {
		int a;
		cin>>a;
		ile[a]++;
		pozycje[a].pb(v);
	}
	rep(i,1,n-1) {
		int v, u, c;
		cin>>v>>u>>c;
		graf[v].pb({u,c});
		graf[u].pb({v,c});
	}
	cin>>q;
	rep(i,1,q) {
		int v, u, c;
		cin>>v>>u>>c;
		zap[i].f.f = v, zap[i].f.s = u;
		zap[i].s = c;
	}
}

void init() {
	dfs1(1,1,0);
	rep(i,1,log-1)
		rep(v,1,n)
			lca[i][v] = lca[i-1][lca[i-1][v]];
}

void solve() {
	rep(i,1,q) {
		int res = zap[i].s;
		if(ile[res] <= sq) {
			if(ile[res] == 0) {
				finalAns[i] = -1;
				continue;
			}
			ll ans = INF;
			int a = zap[i].f.f, b = zap[i].f.s;
			for(auto v: pozycje[res]) 
				ans = min(ans, odl(a,v) + odl(b,v));
			finalAns[i] = ans;
		}
		else {
			if(done[i]) continue;
			//obsluga specjalnej restauracji res, ktora ma wiele wystapien
			rep(v,1,n) dist2[v] = INF;
			for(auto v: pozycje[res]) {
				Q.push({0,v});
				dist2[v] = 0;
			}
			while(Q.size()) {
				int v = Q.top().s;
				ll d = Q.top().f * (-1);
				Q.pop();
				if(dist2[v] < d) continue;
				for(auto it: graf[v]) {
					int u = it.f, kraw = it.s;
					if(dist2[u] > d + kraw) {
						dist2[u] = d + kraw;
						Q.push({-dist2[u],u});
					}
				}
			}
			rep(v,1,n) lca2[0][v] = min(dist2[v], dist2[lca[0][v]]);
			rep(ii,1,log-1)
				rep(v,1,n)
					lca2[ii][v] = min(lca2[ii-1][v], lca2[ii-1][lca[ii-1][v]]);
			rep(j,i,q) {
				if(zap[j].s == res) {
					int v = zap[j].f.f, u = zap[j].f.s;
					ll x = speciallca(v,u);
					done[j] = 1;
					finalAns[j] = odl(v,u) + (2*x);
				}
			}
		}
	}
}
	
	
void wypisz() {
	rep(i,1,q) cout<<finalAns[i]<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	wypisz();
	return 0;
}
