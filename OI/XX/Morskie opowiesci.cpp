#include<bits/stdc++.h>
#define N 5010
#define INF 1000000005
using namespace std;
vector<int> graf[2 * N], pozycje[N];
int n, m, q, ans[1000001], odl[2 * N], visited[2 * N];

int par(int v)
{
	return v<<1;
}
int niepar(int v)
{
	return (v<<1) - 1;
}
struct zap
{
	int v, u, d;
	zap(int a, int b, int c)
	{
		v = a, u = b, d = c;
	}
	zap()
	{
		v = u = d = 0;
	}
}z[1000001];
void ustawOdl(int v)
{
	for(int i = 1; i <= n * 2; i++) odl[i] = INF, visited[i] = 0;
	odl[par(v)] = 0;
}
void bfs(int s)
{
	queue<int> Q;
	Q.push(par(s));
	visited[par(s)] = 1;
	while(Q.size()) {
		int v = Q.front(), dist = odl[v];
		Q.pop();
		for(auto u: graf[v]) {
			if(visited[u] == 0) {
				odl[u] = dist + 1;
				visited[u] = 1;
				Q.push(u);
			}
		}
	}
}
void wczytaj()
{
	cin>>n>>m>>q;
	for(int i = 1; i <= m; i++) {
		int v, u;
		cin>>v>>u;
		graf[par(v)].push_back(niepar(u));
		graf[niepar(v)].push_back(par(u));
		graf[par(u)].push_back(niepar(v));
		graf[niepar(u)].push_back(par(v));
	}
	for(int i = 1; i <= q; i++) {
		int v, u , d;
		cin>>v>>u>>d;
		z[i] = zap(v, u, d);
		pozycje[v].push_back(i);
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	for(int v = 1; v <= n; v++) {
		if(pozycje[v].size()) {
			ustawOdl(v);
			bfs(v);
			for(int i = 0; i < pozycje[v].size(); i++) {
				int zap = pozycje[v][i];
				int u = z[zap].u, d = z[zap].d;
				if(d % 2 == 0) {
					if(v == u) { //corner case parzysta odleglosc start=koniec
						if(graf[par(v)].size()) ans[zap] = 1;
						else ans[zap] = 0;
					}
					else {
						int mini = odl[par(u)];
						if(mini <= d) ans[zap] = 1;
						else ans[zap] = 0;
					}
				}
				if(d % 2 == 1) {
					int mini = odl[niepar(u)];
					if(mini <= d) ans[zap] = 1;
					else ans[zap] = 0;
				}
			}
		}
	}
	for(int i = 1; i <= q; i++) {
		if(ans[i]) cout<<"TAK\n";
		else cout<<"NIE\n";
	}
	return 0;
}
