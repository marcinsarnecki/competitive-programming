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
#define log 20

int out[N], dist[N], nrCyklu[N], rozmiarCyklu[N], order[N];
vector<int> gt[N];//odwrocony graf
int n, q, idx, lca[log][N], visited[N], onStack[N], preorder[N], postorder[N], l;
pii zap[N];

void wczytaj() {
	cin>>n>>q;
	rep(i,1,n) {
		int u;
		cin>>u;
		out[i] = u;
		gt[u].pb(i);//kazdy wierzcholek trzyma liste wierzcholkow, z ktorych wychodza krawedzie do niego (odwrocony graf)
	}
	rep(i,1,q) {
		int v, u;
		cin>>v>>u;
		zap[i] = {v,u};
	}
}

void dfs(int v) {
	visited[v] = 1;
	onStack[v] = 1;
	if(visited[out[v]] == 0)
		dfs(out[v]);
	else if(onStack[out[v]])
		visited[out[v]] = 2;//visited = 2 oznacza ze ten wierzcholek znajduje sie w cyklu
	onStack[v] = 0;
}

void dfscykl(int v, int nr, int odl)
{
	visited[v] = 3;//vis 3 oznacza cykl
	nrCyklu[v] = nr;//v jest w cyklu "nr"
	order[v] = odl;//ustalenie kolejnosci w cyklu
	rozmiarCyklu[nr]++;//aktualizacja rozmiaru cyklu
	if(visited[out[v]] == 1) dfscykl(out[v], nr, odl + 1);
}

void dfslca(int v, int p,int d)//wierzcholek, jego parent
{
	preorder[v] = l++;
	dist[v] = d;
	lca[0][v] = p;
	for(int u: gt[v]) if(visited[u] == 1) dfslca(u, v, d+1);
	postorder[v] = l++;
}

bool przodek(int v, int u) { //czy v jest przodkiem u
	if(preorder[v] < preorder[u] && postorder[v] > postorder[u]) return true;
	return false;
}

int getlca(int v, int u) {//standard lca(v,u)
	if(przodek(v,u)) return v;
	if(przodek(u,v)) return u;
	for(int i = log - 1; i >= 0; i--) //wystarczy skakac potegami 2
		if(!przodek(lca[i][v],u)) 
			v = lca[i][v];
	return lca[0][v];
}


void init() {
	rep(v,1,n) 
		if(visited[v] == 0) //dla kazdego wierzcholka odpalamy podstawowego dfsa ktory znajduje wierzcholki na cyklu
			dfs(v);
	rep(v,1,n) 
		if(visited[v] == 2) //dla kazdego wierzcholka na cyklu odpalamy dfsa, ktory przejdzie sie po cyklach
			dfscykl(v,++idx,0);
	rep(v,1,n) 
		if(visited[v] == 3 && gt[v].size() > 1) //dla kazdego wierzcholka na cyklu do ktorego wpada wiecej niz 1 krawedz
			dfslca(v,v,0);						//wlaczamy dfsa ktory przejdzie sie po "odgalezieniu" doczepionemu do cyklu
	rep(v,1,n) if(visited[v] == 3) lca[0][v] = v;//petelka w korzeniach odgalezien, potrzebne do lca
	rep(i,1,log-1)
		rep(v,1,n)
			lca[i][v] = lca[i-1][lca[i-1][v]];//standard lca
}

void solve() {
	rep(i,1,q) {
		int on = zap[i].f, ona = zap[i].s;
		if(on == ona) {//brzegowy przypadek w ktorym on i ona startuja z tego samego wierzcholka
			cout<<"0 0\n";
			continue;
		}
		if(lca[log-1][on] == lca[log-1][ona]) {//jestesmy w jednym odgalezieniu
			int cel = getlca(on,ona);
			cout<<dist[on] - dist[cel]<<" "<<dist[ona] - dist[cel]<<"\n";
		}
		else if(nrCyklu[lca[log-1][on]] == nrCyklu[lca[log-1][ona]]) {//nie jestesmy w tym samym odgalezieniu ale wpadamy w ten sam cykl
			int v = lca[19][on], u = lca[19][ona];
			int odl1 = dist[on], odl2 = dist[ona];
			
			//case 1: on idzie do niej
			if(order[v] < order[u]) odl1 += order[u] - order[v];
			else odl1 += rozmiarCyklu[nrCyklu[v]] - order[v] + order[u];
			pii ans1(odl1,odl2);
			
			//case 2: ona idzie do niego
			odl1 = dist[on], odl2 = dist[ona];
			if(order[u] < order[v]) odl2 += order[v] - order[u];
			else odl2 += rozmiarCyklu[nrCyklu[v]] - order[u] + order[v];
			pii ans2(odl1,odl2);
			
			if(max(ans1.f,ans1.s) == max(ans2.f,ans2.s)) {//maxy sa rowne, rozpatrujemy minima
				if(min(ans1.f,ans1.s) == min(ans2.f,ans2.s)) {//minima sa rowne, porownujemy dalej
					if(ans1.f > ans2.f)
						cout<<ans1.f<<" "<<ans1.s<<"\n";
					else
						cout<<ans2.f<<" "<<ans2.s<<"\n";
				}
				else if(min(ans1.f,ans1.s) < min(ans2.f,ans2.s)) //minima sa rozne
				cout<<ans1.f<<" "<<ans1.s<<"\n";
				else 
				cout<<ans2.f<<" "<<ans2.s<<"\n";
				
			}
			else if(max(ans1.f,ans1.s) < max(ans2.f,ans2.s)) //maxy sa rozne
				cout<<ans1.f<<" "<<ans1.s<<"\n";
			else 
				cout<<ans2.f<<" "<<ans2.s<<"\n";
		}
		else cout<<"-1 -1\n";//nie da sie
	}
	
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	return 0;
}
