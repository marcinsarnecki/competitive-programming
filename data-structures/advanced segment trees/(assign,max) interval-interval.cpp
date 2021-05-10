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

int tree[NTREE*2], lazy[NTREE*2];

void propagate(int v) {
	if(lazy[v] != 0) {
		tree[v] = lazy[v];
		if(v<NTREE) {
			lazy[v*2] = lazy[v];
			lazy[2*v+1] = lazy[v];
		}
		lazy[v] = 0;
	}
}

void updateRange(int v, int start, int end, int l, int r, int value) {
	propagate(v);
	if(start > r || end < l || start > end) 
		return;
	if(start >= l && end <= r) {
		tree[v] = value;
		if(start != end) {
			lazy[v*2] = value;
			lazy[2*v+1] = value;
		}
		return;
	}
	int mid = (start + end) / 2;
	updateRange(2*v, start, mid, l, r, value);
	updateRange(2*v+1, mid + 1, end, l, r, value);
	tree[v] = max(tree[2*v], tree[2*v+1]);
}

int queryRange(int v, int start, int end, int l, int r) {
	if(start > r || end < l || start > end) 
		return 0;//tutaj wartosc neutralna dla operacji max(), dla liczb nieujemnych 0 wystarczy, w przypadku min query trzeba zwrocic INF
	propagate(v);
	if(start >= l && end <= r) 
		return tree[v];
	int mid = (start + end) / 2;
	int q1 = queryRange(2*v,start,mid,l,r);
	int q2 = queryRange(2*v+1,mid+1,end,l,r);
	return max(q1,q2);
}

int main()
{
	ios_base::sync_with_stdio(0);
	return 0;
}
