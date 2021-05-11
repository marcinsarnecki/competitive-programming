#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 10001
#define NTREE 32768
int tree[2*NTREE], n;
pii odcinki[N];

int query(int p, int k) {
	p += NTREE;
	k += NTREE;
	if(p == k)
		return tree[p];
	int ans = max(tree[p], tree[k]);
	while(k - p > 1) {
		if(p % 2 == 0) ans = max(ans, tree[p+1]);
		if(k % 2 == 1) ans = max(ans, tree[k-1]);
		p /= 2;
		k /= 2;
	}
	return ans;
}

void update(int value, int pos) {
	pos += NTREE;
	while(pos) {
		tree[pos] = max(tree[pos], value); 
		pos /= 2;
	}
}

bool compare(const pii& a, const pii& b) {
	return a.s < b.s;
}

void wej() {
	cin>>n;
	rep(i,1,n)
		cin>>odcinki[i].f>>odcinki[i].s;
}

void solve() {
	sort(odcinki + 1, odcinki + 1 + n, compare);
	for(int i = 1; i <= n; i++) {
		int q = query(0, odcinki[i].f);
		int d = odcinki[i].s - odcinki[i].f;
		update(q + d, odcinki[i].s);
	}
	cout<<query(0,30000);
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	solve();
	return 0;
}
