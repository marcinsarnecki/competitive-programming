#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
using namespace std;
typedef pair<int,int> pii ;
typedef long long ll;

long long Ans = 1, mod = 1e9+7, n, m, H;

struct skladowa{
	long long ans, h;
	pii parent;
	int rank;
};
vector<vector<skladowa>> pole;

struct kraw{
	int x1, y1, x2, y2, h;
	kraw(int a, int b, int c, int d, int e) {
		x1 = a;
		y1 = b;
		x2 = c;
		y2 = d;
		h = e;
	}
	kraw();
};
vector<kraw> kr;
bool compare(const kraw &k1, const kraw &k2) {
	return k1.h < k2.h;
}

void wczytaj() {
	cin>>n>>m>>H;
	if(m > 1)
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j < m; j++) {
				int h;
				cin>>h;
				kr.pb(kraw(j,i,j+1,i,h));
		}
	if(n > 1)
		for(int i = 1; i < n; i++)
			for(int j = 1; j <= m; j++) {
				int h;
				cin>>h;
				kr.pb(kraw(j,i,j,i+1,h));
			}
}

void init() {
	sort(kr.begin(),kr.end(),compare);
	pole.resize(n+1);
	for(int i = 1; i <= n; i++) pole[i].resize(m+1);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			pole[i][j].ans = 1;
			pole[i][j].h = 0;
			pole[i][j].parent = {i,j};
		}
}

pii find(pii v) {
	if(v == pole[v.f][v.s].parent) 
		return v;
	return pole[v.f][v.s].parent = find(pole[v.f][v.s].parent);
}

void union_sets(pii v, pii u, int h) {
	pii a = find(v), b = find(u);
	if(a != b) {
		if(pole[a.f][a.s].rank < pole[b.f][b.s].rank)
			swap(a,b);
		pole[b.f][b.s].parent = a;
		
		long long ans1 = pole[a.f][a.s].ans, ans2 = pole[b.f][b.s].ans;
		long long dif1 = h - pole[a.f][a.s].h, dif2 = h - pole[b.f][b.s].h;
		pole[a.f][a.s].ans = (ans1 + dif1) * (ans2 + dif2) % mod;
		pole[a.f][a.s].h = h;	
		if(pole[a.f][a.s].rank == pole[b.f][b.s].rank)
			pole[a.f][a.s].rank++;
	}
}

void mst() {
	for(auto it: kr) {
		pii a = {it.y1,it.x1}, b = {it.y2,it.x2};
		int h = it.h;
		union_sets(a,b,h);
	}
}

void wypisz_wynik() {
	pii v = find({1,1});
	long long h = pole[v.f][v.s].h;
	Ans = pole[v.f][v.s].ans;
	Ans += H - h;
	cout<<Ans % mod;
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();	
	mst();
	wypisz_wynik();
	return 0;
}
