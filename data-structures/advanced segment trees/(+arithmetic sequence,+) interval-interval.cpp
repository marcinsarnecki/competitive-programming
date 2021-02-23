#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define NTREE 524288

ll tree[NTREE * 2], lazy_a[NTREE * 2], lazy_b[NTREE * 2];

ll ciag(ll p, ll k, ll a, ll b)//suma ciagu arytmetycznego
{
	return (2*b + (k - p)*a) * (k - p + 1) / 2;
}

void update(int v, int start, int end, int l, int r, int a, int b)
{
	int mid = (start + end) /2;
	if(lazy_a[v] != 0 || lazy_b[v] != 0) {
		tree[v] += ciag(start, end, lazy_a[v], lazy_b[v]);
		if(start != end) {
			lazy_a[v * 2] += lazy_a[v];
			lazy_a[v * 2 + 1] += lazy_a[v];
			lazy_b[v * 2] += lazy_b[v];
			lazy_b[v * 2 + 1] += lazy_b[v] + (mid + 1 - start) * lazy_a[v];
		}
		lazy_a[v] = lazy_b[v] = 0;
	}
	
	if(start > r || end < l || start > end)
	{	
		return;
	}
	if(start >= l && end <= r) {
		b += (start - l) * a;
		tree[v] += ciag(start, end, a, b);
		if(start != end) {
			lazy_a[v * 2] += a;
			lazy_b[v * 2] += b;
			lazy_a[v * 2 + 1] += a;
			lazy_b[v * 2 + 1] += b + (mid + 1 - start) * a;
		}
		return;
	}
	update(v * 2, start, mid, l, r, a, b);
	update(v * 2 + 1, mid + 1, end, l, r, a, b);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

ll query(int v, int start, int end, int l, int r)
{
	int mid = (start + end) /2;
	
	if(start > r || end < l || start > end)
		return 0;
		
	if(lazy_a[v] != 0 || lazy_b[v] != 0) {
		tree[v] += ciag(start, end, lazy_a[v], lazy_b[v]);
		if(start != end) {
			lazy_a[v * 2] += lazy_a[v];
			lazy_a[v * 2 + 1] += lazy_a[v];
			lazy_b[v * 2] += lazy_b[v];
			lazy_b[v * 2 + 1] += lazy_b[v] + (mid + 1 - start) * lazy_a[v];
		}
		lazy_a[v] = lazy_b[v] = 0;
	}
	
	if(start >= l && end <= r)
		return tree[v];
	
	ll q1 = query(v * 2, start, mid, l, r);
	ll q2 = query(v * 2 + 1, mid + 1, end, l, r);
	return q1 + q2;
}

int main()
{
	ios_base::sync_with_stdio(0);
	return 0;
}
