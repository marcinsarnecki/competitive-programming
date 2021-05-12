#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define INF 1000000001

#define N 1000001
#define NTREE 1048576

map<int,int> mapa;
int treeile[NTREE * 2];//drzewo na ilosc
ll treesum[NTREE * 2];//drzewo na sume
int n, m;

int skaluj1(int x) { // <x
	auto it = mapa.lower_bound(x);
	return (*it).s - 1;
}

int skaluj2(int x) { // >=x
	auto it = mapa.lower_bound(x);
	return (*it).s;
}

void updateile(int a, int value) {//dodaj/usun liczbe (ilosc)
	int pos = skaluj2(a);
	pos += NTREE;
	while(pos) {
		treeile[pos] += value;
		pos /= 2;
	}
}

int queryile(int s) {//ile liczb >= s
	int l = skaluj2(s), r = skaluj2(INF);
	l += NTREE, r += NTREE;
	int ans = treeile[l] + treeile[r];
	while(r - l > 1) {
		if(l % 2 == 0) ans += treeile[l+1];
		if(r % 2 == 1) ans += treeile[r-1];
		l /= 2;
		r /= 2;
	}
	return ans;
}

void updatesum(int a, int value) {//dodaj/usun liczbe (suma)
	int pos = skaluj2(a);
	pos += NTREE;
	int pom = a * value;
	while(pos) {
		treesum[pos] += pom;
		pos /= 2;
	}
}

ll querysum(int s) {//suma liczb < s
	ll ans = 0;
	int l = NTREE, r = skaluj1(s) + NTREE;
	ans = treesum[l] + treesum[r];
	while(r - l > 1) {
		if(l % 2 == 0) ans += treesum[l+1];
		if(r % 2 == 1) ans += treesum[r-1];
		l /= 2;
		r /= 2;
	}
	return ans;
}

char event[N];
pii input[N];
int kierowcy[N];//ile moze przejechac dany kierowca

void wczytaj() {
	cin>>n>>m;
	rep(i,1,m) 
		cin>>event[i]>>input[i].f>>input[i].s;
}

void init() {
	rep(i,1,m) 
		if(event[i] == 'U')
			mapa[input[i].s] = 0;
	int p = 1;
	for(auto &it: mapa)
		it.s = p++;
	mapa[INF] = p++;//tak dla bezpieczenstwa
}

void solve() {
	rep(i,1,m) {
		if(event[i] == 'U') {
			int k = input[i].f, a = input[i].s;
			if(kierowcy[k] == 0) {//jak pierwszy raz to tylko dodaje
				updateile(a,1);
				updatesum(a,1);
				kierowcy[k] = a;
			}
			else {//jak kierowca kiedys wystapil to trzeba usunac poprzednia wartosc i dodac nowa 
				updateile(kierowcy[k],-1);
				updatesum(kierowcy[k],-1);
				updateile(a,1);
				updatesum(a,1);
				kierowcy[k] = a;
			}
		}
		else {
			ll c = input[i].f, s = input[i].s;
			ll sum = querysum(s) + queryile(s) * s;
			if(sum >= s * c) 
				cout<<"TAK\n";
			else
				cout<<"NIE\n";
		}
 	}
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	return 0;
}
