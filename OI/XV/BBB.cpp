#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
#define N 1000005
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

int n, p, q, x, y, r, ile, Ans[N], k;
int a[N], sumpref[N], minpref[N], minsuf[N];

void wczytaj() {
	cin>>n>>p>>q>>x>>y;
	rep(i,1,n) {
		char z;
		cin>>z;
		if(z == '+') a[i] = 1;
		else a[i] = -1;
	}
}

void init() {
	int sum = 0;
	minpref[0] = minsuf[n+1] = 100;
	rep(i,1,n) {
		sum += a[i];
		sumpref[i] = sum;
		minpref[i] = min(minpref[i-1], sumpref[i]);
	}
	repv(i,n,1)
		minsuf[i] = min(minsuf[i+1], sumpref[i]);
	if(sum != q - p) 
		k = (q - p - sum) / 2;
}
int przedzial(int a1, int b1) {
	return sumpref[b1] - sumpref[a1-1];
}

void solve() {
	//bez przesuniec
	int mini = minpref[n] + p;
	r = (mini * (-1) + 1) / 2;//ruchy na wyrownanie
	if(mini < 0 && k >= 0) ile = 2 * r + k - (2 * min(r,k));
	if(mini < 0 && k < 0) ile = 2 * r + (k * (-1));
	if(mini >= 0 && k >= 0) ile = k;
	if(mini >= 0 && k < 0) ile = k * (-1);
	Ans[1] = ile * x;
	for(int l = 1, i = n; i > 1; i--, l++) {
		int m2 = p + minsuf[i] - przedzial(1,i-1);//minimum prawa strona 
		int m1 = p + przedzial(i,n) + minpref[i-1];
		mini = min(m1,m2);
		r = (mini * (-1) + 1) / 2;//ruchy na wyrownanie
		if(mini < 0 && k >= 0) ile = 2 * r + k - (2 * min(r,k));
		if(mini < 0 && k < 0) ile = 2 * r + (k * (-1));
		if(mini >= 0 && k >= 0) ile = k;
		if(mini >= 0 && k < 0) ile = k * (-1);
		Ans[i] = (ile * x) + (l * y);
	}
	int ans = 1e9;
	rep(i,1,n) ans = min(ans, Ans[i]);
	cout<<ans<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	solve();
	return 0;
}
