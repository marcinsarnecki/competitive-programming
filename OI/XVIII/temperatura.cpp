#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1e9 + 1;

#define N 1000001
#define NTREE 1048576
int n;
int x[N], y[N];
int tree[NTREE*2];

void wej() {
	cin>>n;
	rep(i,1,n) cin>>x[i]>>y[i];
}

int query(int p, int k) {
	p += NTREE, k += NTREE;
	if(p == k)
		return tree[p];
	int ans = max(tree[p], tree[k]);
	while(k - p > 1) {
		if(p % 2 == 0) ans = max(ans, tree[p + 1]);
		if(k % 2 == 1) ans = max(ans, tree[k - 1]);
		p /= 2;
		k /= 2;
	}
	return ans;
}

void init() {
	rep(i,0,2 * NTREE-1) tree[i] = -INF;
	rep(i,1,n) tree[i + NTREE] = x[i];
	repv(i,NTREE-1,1) tree[i] = max(tree[2*i], tree[2*i+1]); 
}

void solve() {
	int ans = 1;
	int i = 1, j = 1;
	while(j < n) {
		j++;
		while(query(i,j) > y[j]) i++;
		ans = max(ans, j - i + 1);
	}
	cout<<ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	init();
	solve();
	return 0;
}
