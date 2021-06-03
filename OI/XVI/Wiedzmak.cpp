#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define INF 1000000000
#define N 201
#define M 3001

int n, m, p, k, ans = INF;
vector<pii> graf[N]; // pary <sasiad, nr krawedzi>
int kowal[N];//maska bitowa miedzy dostepnych w danym miescie
int w[M];//waga krawedzi
int maski[M];//maska bitowa potworow na danej krawedzi
int odl[N][(1<<13)];// [v][mask], minimalna odleglosc do wierzcholka z danym zestawem mieczy

priority_queue<pair<int, pii>> Q; // <odl, <v, mask>>

void wczytaj() {
	cin>>n>>m>>p>>k;
	rep(i,1,k) {
		int a, l, r, mask = 0;
		cin>>a>>l;
		rep(j,1,l) {//mozna scalic wszystkich kowalow w danym miescie
			cin>>r;
			mask |= (1<<(r-1));
		}
		kowal[a] |= mask;
	}
	rep(i,1,m) {
		int a, b, c, l, r, mask = 0;
		cin>>a>>b>>c>>l;
		graf[a].pb({b,i});
		graf[b].pb({a,i});
		w[i] = c;
		rep(j,1,l) {//tak samo z powtorami na krawedzi
			cin>>r;
			mask |= (1<<(r-1));
		}
		maski[i] = mask;
	}
}

void solve() {//rozwiazaniem jest dijkstra z uzyciem masek bitowych
	rep(v,1,n)
		rep(mask,0,(1<<p)-1)
			odl[v][mask] = INF;
	odl[1][kowal[1]] = 0;
	Q.push({0,{1,kowal[1]}});
	while(Q.size()) {
		int v = Q.top().s.f, d = Q.top().f * (-1), mask = Q.top().s.s;//aktualny wierzcholek, odleglosc, maska
		Q.pop();
		if(odl[v][mask] < d) //bezuzyteczny rekord w kolejce priorytetowej
			continue;
		for(auto it: graf[v]) {
			int u = it.f, nr = it.s; //sasiad, nr krawedzi
			int koszt = w[nr], potwory = maski[nr];
			if((potwory | mask) == mask && (d + koszt < odl[u][mask | kowal[u]])) { //jesli jakies potwor wykracza poza nasza maske
				odl[u][mask | kowal[u]] = d + koszt;								                  //to (potwory | mask) nie beda rowne mask
				Q.push({-odl[u][mask | kowal[u]], {u, mask | kowal[u]}});			        //i od razu mozemy uzyc w nastepnym wierzcholku tamtych kowali
			}	
		}
	}
	rep(mask,0,(1<<p)-1)
		ans = min(ans, odl[n][mask]);
	if(ans == INF)
		cout<<"-1\n";
	else
		cout<<ans<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
