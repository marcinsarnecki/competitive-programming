#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 300001
#define NTREE 524288

ll tree[2*NTREE];
int n, m, k, need[N];
vector<int> pozycje[N];//dane panstwo gdzie ma swoje miejsca
int ql[N], qr[N], qvalue[N];//deszcze
int bl[N], br[N], mid[N];//binsearch l r mid
bool unsolved = 1;

void update(int value, int l, int r)
{
	l += NTREE;
	r += NTREE;
	if(l == r) {
		tree[l] += value;
		return;
	}
	tree[l] += value;
	tree[r] += value;
	while(r - l > 1) {
		if(l % 2 == 0) tree[l + 1] += value;
		if(r % 2 == 1) tree[r - 1] += value;
		l /= 2;
		r /= 2;
	}
}

ll query(int pos)
{
	pos += NTREE;
	ll sum = 0;
	while(pos) {
		sum += tree[pos];
		pos /= 2;
	}
	return sum;
}

void clearTree() {
	int idx1 = 1 + NTREE, idx2 = m + NTREE;
	while(idx1 < idx2) {
		rep(i, idx1, idx2)
			tree[i] = 0;
		idx1 /= 2;
		idx2 /= 2;
	}
}

bool compare(int a, int b) {
	return mid[a] < mid[b];
}

void input() {
	cin>>n>>m;
	rep(i,1,m) {
		int o;
		cin>>o;
		pozycje[o].pb(i);
	}
	rep(i,1,n)
		cin>>need[i];
	cin>>k;
	rep(i,1,k)
		cin>>ql[i]>>qr[i]>>qvalue[i];
}

void deszcz(int i) {
	if(ql[i] <= qr[i]) 
		update(qvalue[i], ql[i], qr[i]);
	else {
		update(qvalue[i], ql[i], m);
		update(qvalue[i], 1, qr[i]);
	}
}

bool check(int i) {
	ll sum = 0;
	for(auto pos: pozycje[i]) {
		sum += query(pos);
		if(sum >= need[i]) //long long overflow 10^9 * m * m
			return true;
	}
	return false;
}

void main_binsearch_move() {
	vector<int> rest;
	rep(i,1,n) {
		if(bl[i] <= br[i]) {//panstwa dla ktorych ich binsearch sie jeszcze nie skonczyl
			mid[i] = (bl[i] + br[i]) / 2;
			rest.pb(i);
		} 
	}
	if(rest.size() == 0) {//znaleziono odpowiedz dla wszystkich panstw
		unsolved = 0;
		return;
	}
	sort(rest.begin(), rest.end(), compare);//sort panstw po ich indywidualnych midach z binsearcha
	int kdx = 1;
	for(auto panstwo: rest) { //symulujemy po kolei wszystkie deszcze, w tle wykonujemy po jednym kroku dla n binsearchow
		while(kdx <= mid[panstwo]) 
			deszcz(kdx++);
		if(check(panstwo)) 
			br[panstwo] = mid[panstwo] - 1;
		else 
			bl[panstwo] = mid[panstwo] + 1;
	}
	clearTree();
}

void solve() { // log k razy wykonujemy n binsearchow
	rep(i,1,n) {
		bl[i] = 1;
		br[i] = k;
	}
	while(unsolved)
		main_binsearch_move();
	rep(i,1,n)
		if(br[i] + 1 == k + 1) //odpowiedzia jest r+1 z binsearcha
			cout<<"NIE\n";
		else
			cout<<br[i]+1<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	solve();
	return 0;
}
