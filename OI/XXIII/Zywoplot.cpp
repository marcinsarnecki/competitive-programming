#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1001

int n, m, all, cis, ansvertical[N][N], anshorizontal[N][N];

pii p[N][N];//find union
int r[N][N];

struct edge{
public:
	int i1, j1, i2, j2, value;
	edge(int a, int b, int c, int d, int e):i1(a),j1(b),i2(c),j2(d),value(e){}
	edge(){i1=j1=i2=j2=value=0;}
};

vector<edge> e;

bool cmp(const edge& a, const edge& b) {
	return a.value < b.value;
}

void input() {
	cin>>n>>m;
	string line;
	rep(i,1,n) {
		cin>>line;
		rep(j,1,m-1){
			all++;
			if(line[j-1] == 'C') {
				e.pb(edge(i,j,i,j+1,1));
				cis++;
			}
			else 
				e.pb(edge(i,j,i,j+1,0));
		}
	}
	rep(i,1,n-1) {
		cin>>line;
		rep(j,1,m) {
			all++;
			if(line[j-1] == 'C') {
				cis++;
				e.pb(edge(i,j,i+1,j,1));
			}
			else 
				e.pb(edge(i,j,i+1,j,0));
		}
	}
}

pii find(pii v) {
	if(p[v.f][v.s] == v)
		return v;
	return p[v.f][v.s] = find(p[v.f][v.s]);
}

bool union_sets(pii v, pii u) {
	v = find(v);
	u = find(u);
	if(v == u)
		return false;
	if(r[v.f][v.s] < r[u.f][u.s])
		swap(v, u);
	r[v.f][v.s] += r[u.f][u.s];
	p[u.f][u.s] = v;
	return true;
}

void init() {
	rep(i,1,n)
		rep(j,1,m) {//find union init
			r[i][j] = 1;
			p[i][j] = {i,j};
		}
}

void solve() {
	sort(e.begin(), e.end(), cmp);
	for(auto it: e) {
		if(union_sets({it.i1, it.j1}, {it.i2, it.j2})) {
			all--;
			if(it.value == 1) 
				cis--;
			if(it.i1 == it.i2)
				ansvertical[it.i1][it.j1] = -1;
			else
				anshorizontal[it.i1][it.j1] = -1;
		}
	}
	cout<<all<<" "<<cis<<"\n";//liczba zywoplotow to liczba wszystkich krawedzi w grafie - krawedzie uzyte do zbudowania drzewa
	rep(i,1,n) {
		rep(j,1,m-1)
			if(ansvertical[i][j] == 0)
				cout<<'Z';
			else
				cout<<'.';
		cout<<"\n";
	}
	rep(i,1,n-1) {
		rep(j,1,m)
			if(anshorizontal[i][j] == 0)
				cout<<'Z';
			else
				cout<<'.';
		cout<<"\n";
	}
	
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	init();
	solve();
	return 0;
}
