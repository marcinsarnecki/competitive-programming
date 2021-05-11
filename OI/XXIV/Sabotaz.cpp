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
double morale[N];
vector<int> graf[N], przeskoki;
double ans;

void wej() {
	cin>>n>>k;
	rep(i,2,n) {
		int u;
		cin>>u;
		graf[u].pb(i);
	}
}

void dfs(int v) {//dfs do rozmiarow 
	for(auto u: graf[v])
		dfs(u);
	roz[v] = 1;
	bool b = 0;//czy istnieje dziecko o rozmiarze <= k
	for(auto u: graf[v]) {
		roz[v] += roz[u];
		if(roz[u] <= k) b = 1;
	}
	if(b && roz[v] > k) przeskoki.pb(v);//rozmiar v jest > k, a przynajmniej jedno dziecko ma rozmiar <= k, wiec v trzeba uwzglednic przy liczeniu wyniku koncowego
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
		m = max(m, min((double)roz[u] / (roz[v] - 1), morale[u]));//max z minimow (minimalny wynik aby nie wybuchl bunt w dziecku, rozmiar dziecka / rozmiar calego poddrzewa - 1)
	morale[v] = m;//minimalne morale aby v na pewno sie nie zbuntowal
}

void wypiszWynik() {
	for(auto v: przeskoki) ans = max(ans, morale[v]);
	cout<<ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	dfs(1);
	dfs2(1);
	wypiszWynik();
	return 0;
}
