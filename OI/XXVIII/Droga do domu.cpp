#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = (ll) 1000000 * 1000000 * 1000000;

#define N 10001
#define S 25001

int n, m, s, k, t;

vector<int> trasy[S];
vector<ll> sumpref[S];//sumt prefiksowe dla tras
unordered_map<int,int> graf[N];
pii czasy[S];//czasy wyruszenia, co ile nastepny
ll dp[N][2];//potrzeba tylko 2 stanow, mozna na zmiane miedzy 0 i 1, nie potrzeba 100 stanow

ll najwczesniejszy(int i, int j, ll time) {
	ll first = czasy[i].f + sumpref[i][j];
	if(time <= first)
		return first;//jesli musimy czekac to biezemy pierwszy autobus ktory przyjedzie
	ll diff = time - first;
	return first + (diff + czasy[i].s-1) / czasy[i].s * czasy[i].s;//pierwszy ktory moze przyjechac
}

void wczytaj() {
	cin>>n>>m>>s>>k>>t;
	rep(i,1,m) {
		int a, b, c;
		cin>>a>>b>>c;
		graf[a][b] = c;
		graf[b][a] = c;
	}
	rep(i,1,s) {
		int l, x, y, v;
		cin>>l>>x>>y;
		czasy[i] = {x,y};
		rep(j,1,l) {
			cin>>v;
			trasy[i].pb(v);
		}
		sumpref[i].resize(l, 0);
		rep(j,1,l-1) //dla kazdej trasy liczymy sume prefiksowa
			sumpref[i][j] = sumpref[i][j-1] + graf[trasy[i][j-1]][trasy[i][j]];
	}
}

void solve() {
	rep(v,1,n) dp[v][1] = INF;
	dp[1][1] = t;
	for(int p = 0; p <= k; p++) {//przesiadki
		rep(v,1,n) dp[v][0] = dp[v][1];
		for(int i = 1; i <= s; i++) { //trasy
			ll current = INF;//poczatkowo najlepszy autobus na danej trasie nie istnieje (w pierwszym wierzcholku dopiero obliczymy go) 
			for(int j = 0; j < trasy[i].size()-1; j++) {//kolejne wierzcholki na trasie, dla kazdego liczymy kiedy moze przyjechac
				int v =  trasy[i][j], u = trasy[i][j+1];//najwczesniejszy autobus w to miejsce od momentu min(current, dp[v][0]) 
				current = najwczesniejszy(i,j,min(current, dp[v][0]));//current to najlepszy biezacy autobus ktorym jedziemy po trasie, bierzemy minimum z niego i dynamika dla tego wierzcholka
				current += graf[v][u];
				dp[u][1] = min(dp[u][1], current);//probujemy polepszyc wynik
			}	
		}
	}
	if(dp[n][1] == INF)
		cout<<"NIE\n";
	else 
		cout<<dp[n][1]<<"\n";
	
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
