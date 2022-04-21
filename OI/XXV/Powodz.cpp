#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

ll Ans = 1, mod = 1e9+7, n, m, H;

struct node{
	ll ans, h;
	pii parent;
	int size;
};
vector<vector<node>> field;

struct edge{
	int x1, y1, x2, y2, h;
	edge(int a, int b, int c, int d, int e){
		x1 = a;                                                                 
        y1 = b;                                                                 
        x2 = c;                                                                 
        y2 = d;                                                                 
        h = e;
	}
	edge();
};
vector<edge> edges;

bool compare(const edge &e1, const edge &e2) {
	return e1.h < e2.h;
}

void input() {
	cin>>n>>m>>H;
	if(m > 1)
		rep(i,1,n)
			rep(j,1,m-1) {
				int h; cin>>h;
				edges.pb(edge(j,i,j+1,i,h));
		}
	if(n > 1)
		rep(i,1,n-1)
			rep(j,1,m) {
				int h; cin>>h;
				edges.pb(edge(j,i,j,i+1,h));
			}
}

void init() {
	sort(edges.begin(),edges.end(),compare);
	field.resize(n+1);
	rep(i,1,n) //dynamiczne utworzenie pola o rozmiarze n * m
		field[i].resize(m+1);
	rep(i,1,n)
			rep(j,1,m) { 
			field[i][j].ans = 1;//w kazdym polu poczatkowo mozna ustawic wode na 1 sposob 
			field[i][j].h = 0;//do wysokosci 0
			field[i][j].parent = {i,j};//find union poczatek
			field[i][j].size = 1;
		}
}

pii find(pii v) {
	if(v == field[v.f][v.s].parent) 
		return v;
	return field[v.f][v.s].parent = find(field[v.f][v.s].parent);
}

void union_sets(pii v, pii u, int h) {
	pii a = find(v), b = find(u);
	if(a != b) {
		if(field[b.f][b.s].size < field[a.f][a.s].size)
			swap(a,b);
		field[a.f][a.s].parent = b;//dolaczamy (mniejsze) a do (wiekszego) b
		field[b.f][b.s].size += field[a.f][a.s].size;
		
		ll ans1 = field[a.f][a.s].ans, ans2 = field[b.f][b.s].ans;
		ll dif1 = h - field[a.f][a.s].h, dif2 = h - field[b.f][b.s].h;
		field[b.f][b.s].ans = (ans1 + dif1) * (ans2 + dif2) % mod;//liczba sposobow ustawienia wody w nowym polaczonym obszarze
		field[b.f][b.s].h = h;
	}
}

void mst() {
	for(auto it: edges) {//kruskal
		pii a = {it.y1,it.x1}, b = {it.y2,it.x2};
		int h = it.h;
		union_sets(a,b,h);
	}
}

void print() {
	pii v = find({1,1});
	ll h = field[v.f][v.s].h;
	Ans = field[v.f][v.s].ans;
	Ans += H - h;//sciana dokola calych danych
	cout<<Ans % mod<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	init();	
	mst();
	print();
	return 0;
}
