#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 1001
#define log 18
vector<pii> graf[N];//graf wazony, pary <sasiad,waga>
int preorder[N], postorder[N], ldx, lca[log][N], lca2[log][N], n;//lca przechowuje skok, lca2 maksimum na skoku

void dfs(int v, int p, int w) {
	lca[0][v] = p;
	lca2[0][v] = w;
	preorder[v] = ++ldx;
	for (auto u : graf[v])
		if (u.f != p)
			dfs(u.f, v, u.s);
	postorder[v] = ++ldx;
}

bool przodek(int v, int u) { //czy v jest przodkiem u
	if(v == u)
		return true;
	if (preorder[v] < preorder[u] && postorder[v] > preorder[u]) return true;
		return false;
}

int lcamax(int v, int u) {//max kraw na sciezce v-u //min dzialaloby tak samo, jedynie na poczatku ans musialoby byc rowne +INF 
	int ans = 0;
	if (przodek(v, u)) {
		repv(i, log - 1, 0) if (!przodek(lca[i][u], v)) {
			ans = max(ans, lca2[i][u]);
			u = lca[i][u];
		}
		ans = max(ans, lca2[0][u]);
		return ans;
	}
	if (przodek(u, v)) {
		repv(i, log - 1, 0) if (!przodek(lca[i][v], u)) {
			ans = max(ans, lca2[i][v]);
			v = lca[i][v];
		}
		ans = max(ans, lca2[0][v]);
		return ans;
	}
	repv(i, log - 1, 0) if (!przodek(lca[i][v], u)) {
		ans = max(ans, lca2[i][v]);
		v = lca[i][v];
	}
	repv(i, log - 1, 0) if (!przodek(lca[i][u], v)) {
		ans = max(ans, lca2[i][u]);
		u = lca[i][u];
	}
	ans = max(ans, lca2[0][v]);
	ans = max(ans, lca2[0][u]);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin >> n;
	rep(i, 1, n - 1) {
		int v, u, c;
		cin >> v >> u >> c;
		graf[v].pb({ u,c });
		graf[u].pb({ v,c });
	}
	dfs(1, 1, 0);
	rep(i, 1, log - 1)
		rep(v, 1, n)
			lca[i][v] = lca[i - 1][lca[i - 1][v]];
	rep(i, 1, log - 1)
		rep(v, 1, n)
			lca2[i][v] = max(lca2[i - 1][v], lca2[i - 1][lca[i - 1][v]]);
	//od teraz lcamax(v,u) zwraca maksymalna krawedz na sciezce v-u
	return 0;
}
