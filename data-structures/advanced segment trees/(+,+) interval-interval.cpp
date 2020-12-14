#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define NTREE 1048576
ll tree[NTREE * 2], lazy[NTREE * 2];

void update(int v, int start, int end, int l, int r, int value)
{
	if(lazy[v] != 0) {
		tree[v] += (end - start + 1) * lazy[v];
		if(start != end) {
			lazy[v * 2] += lazy[v];
			lazy[v * 2 + 1] += lazy[v]; 
		}
		lazy[v] = 0;
	}
	
	if(start > r || end < l || start > end) 
		return;
	
	if(start >= l && end <= r) {
		tree[v] += (end - start + 1) * value;
		if(start != end) {
			lazy[v * 2] += value; 
			lazy[2 * v + 1] += value; 
		}
		return;
	}
	
	int mid = (start + end) / 2;
	update(v * 2, start, mid, l, r, value);
	update(v * 2 + 1, mid + 1, end, l, r, value);
	tree[v] = tree[v * 2] + tree[v * 2 + 1];
}

ll query(int v, int start, int end, int l, int r)
{
	if(start > r || end < l || start > end) 
		return 0;
	
	if(lazy[v] != 0) {
		tree[v] += (end - start + 1) * lazy[v];
		if(start != end) {
			lazy[2 * v] += lazy[v];
			lazy[2 * v + 1] += lazy[v];
		}
		lazy[v] = 0;
	}
	
	if(start >= l && end <= r)
		return tree[v];
	
	int mid = (start + end) / 2;
	ll q1 = query(2 * v, start, mid, l, r);
	ll q2 = query(2 * v + 1, mid + 1, end, l, r);
	return q1 + q2;
}


int main()
{
	ios_base::sync_with_stdio(0);
	return 0;
}
