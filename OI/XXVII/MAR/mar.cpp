#include<bits/stdc++.h>
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define ll long long
#define N 100010
using namespace std;

int n, m, zap[10001];
int tab[N];
unordered_map<int,int> mapa[18];

int all[18];

void wczytaj() {
	cin>>n>>m;
	char z;
	rep(i,1,n) {
		cin>>z;
		tab[i] = z - 48;
	}
	rep(i,1,m) cin>>zap[i];
}

int gethash(int pos, int len) {
	int ans = 0;
	for(int i = pos + len - 1, p = 0; i >= pos; i--, p++)//error
		ans += tab[i] * (1<<p);
	return ans;
}

void init() {
	all[0] = 0;
	rep(i,1,17) all[i] = (1<<i);
	rep(len,1,min(17,n))
		rep(i,1,n-len+1) {
			int num = gethash(i,len);
			mapa[len][num]++;
		}
	
}

int findAns() {
	rep(i,1,17)
		if(mapa[i].size() < all[i]) return i;
}

void wywal_hash(int h, int len) {
	if(--mapa[len][h] == 0) {
		auto it = mapa[len].find(h);
		mapa[len].erase(it);
	}
}

void wywal_len(int pos, int len) {
	if(len > n) return;
	int i = max(1,pos - len + 1);
	int h = gethash(i,len);
	for(;i <= min(pos,n - len + 1); i++) {
		wywal_hash(h,len);
		h<<=1;
		h += tab[i + len];
		if(h & (1<<len)) h -= (1<<len);
	}
}

void dodaj_len(int pos, int len) {
	if(len > n) return;
	int i = max(1,pos - len + 1);
	int h = gethash(i,len);
	for(;i <= min(pos,n - len + 1); i++) {
		mapa[len][h]++;
		h<<=1;
		h += tab[i + len];
		if(h & (1<<len)) h -= (1<<len);
	}
	
}

void solve() {
	int ans = findAns();
	cout<<ans<<"\n";
	
	rep(q,1,m) {
		int pos = zap[q];
		
		rep(len,1,17) 
			wywal_len(pos,len);//wywalam
			
		if(tab[pos] == 0) tab[pos] = 1;//zmieniam
		else tab[pos] = 0;
			
		rep(len,1,17)
			dodaj_len(pos,len);//dodaje
			
		ans = findAns();//wypisuje wynik
		cout<<ans<<"\n";
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	return 0;
}
