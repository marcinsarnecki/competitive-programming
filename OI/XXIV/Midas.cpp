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

int n, q, idx = 1, l[N], r[N];//graf
int nr[N];//w jakiej grupie
vector<int> grupy[N];
queue<int> Q;
pii zap[N];

void wczytaj() {
	cin>>n;
	rep(i,1,n)
		cin>>l[i]>>r[i];
	cin>>q;
	rep(i,1,q) 
		cin>>zap[i].f>>zap[i].s;
}

void dfs(int v) {//ten dfs znajduje wierzcholki do ktorych koszt=1 i dodaje je do poczatkowej grupy numer 1
	if(r[v]) 
		grupy[1].pb(r[v]);
	if(l[v]) 
		dfs(l[v]);
}

void solve() {
	dfs(1);
	Q.push(1);
	while(!Q.empty()) {
		int id = Q.front();
		Q.pop();
		for(auto v: grupy[id]) 	//w kazdej grupie wierzcholkow nadajemy numery, i jesli istnieja nastepne wierzcholki to tworzymy nastepne grupy, kolejnosc w przechodzeniu bfs gwarantuje poprawnosc 
			nr[v] = id;			//o kosztach dla wierzcholkow mozna pomyslec jak o indeksach w drzewie przedzialowym
		bool b1 = 0, b2 = 0;
		for(auto v: grupy[id]) {
			if(l[v]) b1 = 1;
			if(r[v]) b2 = 1;
		}
		if(b1) { //czy budowac lewa krawedz
			idx++;
			for(auto v: grupy[id])
				if(l[v])
					grupy[idx].pb(l[v]);
			Q.push(idx);
		}
		if(b2) { //czy budowac prawa krawedz
			idx++;
			for(auto v: grupy[id])
				if(r[v])
					grupy[idx].pb(r[v]);
			Q.push(idx);
		}
	}
	rep(i,1,q)
		if(nr[zap[i].f] >= nr[zap[i].s])
			cout<<"TAK\n";
		else
			cout<<"NIE\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
