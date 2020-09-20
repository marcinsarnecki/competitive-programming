#include<bits/stdc++.h>
using namespace std;
int inf = 36500;
vector<int> graf[1000005];
vector<int> visited, stos, wej, drogi;
int n, m, ans, cnt;

void dfs1(int v)
{
	stos[v] = 1;
	visited[v]++;
	for(int u: graf[v]) {
		if(visited[u] == 0) dfs1(u);// visited == 1 oznacza odwiedzony, 2 oznacza ze wierzcholek w cyklu
		else if(stos[u] == 1) visited[u] = 2;
	}
	stos[v] = 0;
}

void dfs2(int v)
{
	visited[v] = 2;
	for(int u: graf[v]) {
		if(visited[u] == 1) dfs2(u);//wierzcholki nieskonczone zaznaczam na 2
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		int wa, wb;
		cin>>wa>>wb;
		graf[wb].push_back(wa);
	}
	
	visited.assign(n + 2, 0);
	stos.assign(n + 2, 0);
	
	dfs1(n + 1);
	
	for(int i = 1; i <= n + 1; i++) if(visited[i] == 2) dfs2(i);

	stos.clear();
	stos.shrink_to_fit();
    
    drogi.assign(n + 2, 0);
    
    for(int i = 1; i <= n + 1; i++) {
		if(visited[i] == 2) drogi[i] = inf;
		if(visited[i] == 0) drogi[i] = -1;
	}

    visited.clear();
    visited.shrink_to_fit();
    wej.assign(n + 2, 0);
    
    for(int i = 1; i <= n + 1; i++) if(drogi[i] == 0) for(int u: graf[i]) wej[u]++;//stopnie wejscia dla wierzcholkow bez cykli
    
    if(drogi[n + 1] == 0)
    {		
  		queue<int> Q;
  		Q.push(n + 1);
  		drogi[n + 1] = 1;
  		while(!Q.empty())
  		{
  			int v = Q.front();
			Q.pop();
			for(int u: graf[v]) {
				drogi[u] = min(inf, drogi[u] + drogi[v]);
				wej[u]--;
				if(wej[u] == 0) Q.push(u);
			}	  	
		}
	}
    
    for(int i = 1; i <= n; i++) ans = max(ans, drogi[i]);
    for(int i = 1; i <= n; i++) if(drogi[i] == ans) cnt++;
	
	if(ans == inf) cout<<"zawsze\n";
	else cout<<ans<<"\n";
	cout<<cnt<<"\n";
	for(int i = 1; i <= n; i++) if(drogi[i] == ans) cout<<i<<" "; 
	return 0;
}
