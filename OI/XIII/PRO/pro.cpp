#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000002
int INF = 36500;
vector<int> graf[N];
vector<int> visited, stos, ile, wej;//ile - ile sciezek konczy sie w danym wierzcholku
int n, m, ans, l;
queue<int> Q;

void wczytaj() {
	cin>>n>>m;
	rep(i,1,m) {
		int v, u;
		cin>>v>>u;
		graf[u].pb(v);//na odwrot!!!
	}
}

void dfs1(int v)
{
	stos[v] = 1;
	visited[v] = 1;
	for(int u: graf[v]) {
		if(visited[u] == 0) dfs1(u);// visited == 1 oznacza odwiedzony, 2 oznacza ze wierzcholek w cyklu
		else if(stos[u] == 1) visited[u] = 2;
	}
	stos[v] = 0;
}

void dfs2(int v)
{
	visited[v] = 2;
	for(int u: graf[v]) 
		if(visited[u] == 1) dfs2(u);//wierzcholki nieskonczone zaznaczam na 2
}

void cykle() {
	visited.resize(n + 2, 0);
	stos.resize(n + 2, 0);
	dfs1(n + 1);//szuka wierzcholkow na cyklu
	rep(i,1,n+1)//wszystkim wierzcholkom na cyklu + tm do ktorych mozna dojsc z cyklu zaznacza visited = 2
		if(visited[i] == 2)
			dfs2(i);
	stos.clear();
	stos.shrink_to_fit();//pamiec
	ile.resize(n + 2, 0);
	rep(i,1,n+1) {
		if(visited[i] == 2) ile[i] = INF;//wierzcholku na cyklu i za cyklami ile = INF
		if(visited[i] == 0) ile[i] = -1;
	}
	visited.clear();
	visited.shrink_to_fit();//pamiec
}

void solve() {
	wej.resize(n + 2, 0);
	rep(i,1,n+1) 
		if(ile[i] == 0)
			for(int u: graf[i])
				wej[u]++;
	if(ile[n + 1] == 0) {	
  		Q.push(n + 1);
  		ile[n + 1] = 1;
  		while(!Q.empty()) {
  			int v = Q.front();
			Q.pop();
			for(int u: graf[v]) {
				ile[u] = min(INF, ile[u] + ile[v]);
				wej[u]--;
				if(wej[u] == 0) Q.push(u);
			}	  	
		}
	}
	rep(i,1,n) ans = max(ans, ile[i]);
	rep(i,1,n) if(ile[i] == ans) l++;
	if(ans == INF)
		cout<<"zawsze\n";
	else
		cout<<ans<<"\n";
	cout<<l<<"\n";
	rep(i,1,n)
		if(ile[i] == ans)
			cout<<i<<" ";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	cykle();
	solve();
	return 0;
}
