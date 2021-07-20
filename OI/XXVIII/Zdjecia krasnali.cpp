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
int n, m, nr[N], InDegree[N], used[N], current = 1;
vector<int> graf[N];
queue<int> Q;

void input() {//wierzcholki 1 i 2 musza miec skrajne numery (1 i n)
	cin>>n>>m;//kazdy inny wierzcholek musi miec doklanie polowe sasiadow wiekszych od niego i polowe sasiadow mniejszych od niego
	rep(i,1,m) {//wierzcholki mozemy uporzadkowac rosnaco, wtedy na brzegach mamy 1 i 2 z numerami 1 i n
		int a, b;//reszta wierzcholkow musi miec polowe swoich krawedzi z lewej strony, a polowe z prawej
		cin>>a>>b;//krawedzie mozna skierowac (np od mniejszych do wiekszych numerow)
		graf[a].pb(b);//wtedy Indegree[v] oznacza stopien wejscia kazdego wierzcholka
		graf[b].pb(a);
	}
}

void solve() {
	InDegree[2] = graf[2].size();//wierzcholek koncowy wyjatkowo ma stopien wejscia rowny ilosci krawedzi (bo jest wiekszy od wszystkich innych wierzcholkow)
	rep(i,3,n)
		InDegree[i] = graf[i].size() / 2;//reszta ma stopien wejscia rowny polowie wszystkich krawedzi
	Q.push(1);
	while(Q.size() > 0) {//jesli rozwiazanie istnieje, to znajdziemy je podczas sortowania topologicznego
		int v = Q.front();
		Q.pop();
		nr[v] = current++;//kolejne numery sie zwiekszaja
		used[v] = 1;
		for(auto u: graf[v]) {
			if(used[u]) //nie robimy nic z krawedziami w lewa strone
				continue;
			if(--InDegree[u] == 0)//pushujemy wierzcholek jesli przetworzylismy polowe jego wszystkich krawedzi (wszystkie z lewej)
				Q.push(u);
		}
	}
	rep(i,1,n)
		if(nr[i] == 0 && graf[i].size() == 0) //"samotnym" wierzcholkom tez trzeba przypisac numery
			nr[i] = current++;
	rep(i,3,n) {
		int l1 = 0, l2 = 0;
		for(auto u: graf[i])
			if(nr[u] < nr[i])
				l1++;
			else
				l2++;
		if(l1 != l2) {//sprawdzamy czy dla kazdego wierzcholka zgadza sie warunek z tresci
			cout<<"NIE\n";
			return;
		}
	}
	cout<<"TAK\n";
	rep(i,1,n)
		cout<<nr[i]<<" ";
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	solve();
	return 0;
}
