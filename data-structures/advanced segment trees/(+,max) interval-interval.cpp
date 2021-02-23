#include<bits/stdc++.h> //drzewo przedzialowe przedzial-przedzial +,max
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define NTREE 65536
ll tree[NTREE * 2], lazy[NTREE * 2];//tree trzyma maxy, a lazy + na przedzial
int n, m, z;

void update(int v, int start, int end, int l, int r, int value)
{
	if(lazy[v] != 0) {
		tree[v] += lazy[v];
		if(start != end) {
			lazy[v * 2] += lazy[v];
			lazy[v * 2 + 1] += lazy[v];//PRZEKAZUJEMY NA DOL LAZY[V] 
		}
		lazy[v] = 0;
	}
	
	if(start > r || end < l || start > end)
		return;
	
	if(start >= l && end <= r) {
		tree[v] += value;
		if(start != end) {
			lazy[v * 2] += value;
			lazy[2 * v + 1] += value;//PRZEKAZUJEMY NA DOL VALUE
		}
		return;
	}
	
	int mid = (start + end) / 2;
	update(2 * v, start, mid, l, r, value);
	update(2 * v + 1, mid + 1, end, l , r, value);
	tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

ll query(int v, int start, int end, int l, int r)
{
	if(start > r || end < l || start > end)
		return 0;
	
	if(lazy[v] != 0) {
		tree[v] += lazy[v];
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
	return max(q1, q2);
}


int main()
{
	ios_base::sync_with_stdio(0);
	return 0;
}
