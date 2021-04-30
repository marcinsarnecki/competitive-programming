#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 100001
int n, m, ans[N];
bool visited[N], stos[N];
vector<int> graf[N], pom;
bool ok = true;//czy uzyta // visited


void dfs1(int v, int p) { //znalezienie wierzcholka i krawedzi na cyklu
    visited[v] = 1;
    stos[v] = 1;
    for(auto u: graf[v])
        if(visited[u] == 0)
            dfs1(u, v);
        else if(stos[u] && u != p) { //jesli napotykamy na wierzcholek 'u' ktory jest na stosie i nie jest poprzednikiem 'v' to dodajemy 'v' i krawedz do 'u' do vectora pomocniczego 
            ans[v] = u;
            pom.pb(v);
        }
    stos[v] = 0;
}

void dfs2(int v, int p) { //'p' potrzebne jest aby dfs2 przy pierwszym wierzcholku nie przeszedl przez krawedz ktora zostala przypisana wierzcholkowi 'v'
    ans[v] = p;
    visited[v] = 1;
    for(auto u: graf[v])
        if(visited[u] == 0 && u != p)
            dfs2(u, v);
}

void wczytaj() {
	cin>>n>>m;
    rep(i,1,m) {
        int v, u;
        cin>>v>>u;
        graf[v].pb(u);
        graf[u].pb(v);
    }
}

void solve() {
    rep(i,1,n)
        if(visited[i] == 0)
            dfs1(i,0);
    rep(i,1,n)
        visited[i] = 0;
    for(auto v: pom)
        dfs2(v, ans[v]);
    rep(i,1,n)
        if(ans[i] == 0) { //dfs1 nie znajdzie zadnego wierzcholka w drzewie wiec jesli bylo jakies drzewo to tam wierzcholki nie zostaly obsluzone przez dfs2, od razu NIE
            cout<<"NIE\n";
            return;
        }
    cout<<"TAK\n";
    rep(i,1,n)
        cout<<ans[i]<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
