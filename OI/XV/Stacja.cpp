#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000001

vector<int> graf[N];
int n, lowerAmount[N];
ll ans[N], lowerSum[N];

void wczytaj() {
	cin>>n;
	rep(i,1,n-1) {
		int a, b;
		cin>>a>>b;
		graf[a].pb(b);
		graf[b].pb(a);
	}
}

void dfs1(int v, int p) {
	for(auto u: graf[v])
		if(u != p)
			dfs1(u, v);
	lowerAmount[v] = 1;										//poczatkowo ilosc wierzcholkow w poddrzewie na 1
	for(auto u: graf[v])
		if(u != p) {
			lowerAmount[v] += lowerAmount[u];				//ilosc wierzcholkow w poddrzewie
			lowerSum[v] += lowerSum[u] + lowerAmount[u];	//suma odleglosci do wierzcholka v ze wszystkich wierzcholkow z poddrzewa
		}
}

void dfs2(int v, int p, ll upperSum, int upperAmount) {		//ten dfs wchodzac do wierzcholkow zapamietuje ile jest wierzcholkow nad nim + sume odleglosci ze wszystkich wierzcholkow nad nim
	ans[v] = upperSum + lowerSum[v];						//maksujemy odpowiedz dla wierzcholka sumujac te dwie wartosci
	for(auto u: graf[v])
		if(u != p) 
			dfs2(u, v, (ll)		lowerSum[v] - lowerSum[u] - lowerAmount[u] +				//suma odleglosci w poddrzewie nie liczac odgalezienia od ktorego idziemy
								upperSum + 						//suma odleglosci nad wierzcholkiem
								upperAmount + lowerAmount[v] - lowerAmount[u],		//dodac ilosc wierzcholkow (poniewaz kazda odleglosc zwiekszy sie o 1, wiec wystarczy dodac ilosc wierzcholkow)
								upperAmount + lowerAmount[v] - lowerAmount[u]);		//sama ilosc
}

void solve() {
	dfs1(1, 1);
	dfs2(1,1,0,0);
	int best = 1;
	rep(i,2,n)
		if(ans[i] > ans[best]) 
			best = i;
	cout<<best;
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
