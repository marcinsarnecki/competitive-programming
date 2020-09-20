#include<bits/stdc++.h>//drzewo przedzialowe przedzial-przedzial +,max
#define NTREE 65536
using namespace std;
long long tree[NTREE * 2], lazy[NTREE * 2];//tree trzyma maxy, a lazy + na przedzial
int n, m, z;

void update(int v, int start, int end, int l, int r, int value)
{
	if(lazy[v] != 0) {
		tree[v] += lazy[v];
		if(start != end) {
			lazy[v * 2] += lazy[v];
			lazy[v * 2 + 1] += lazy[v];//PRZEKAZUJEMY NA DOL LAZY[V]!!! 
		}
		lazy[v] = 0;
	}
	
	if(start > r || end < l || start > end)
		return;
	
	if(start >= l && end <= r) {
		tree[v] += value;
		if(start != end) {
			lazy[v * 2] += value;
			lazy[2 * v + 1] += value;//PRZEKAZUJEMY NA DOL VALUE!!!
		}
		return;
	}
	
	int mid = (start + end) / 2;
	update(2 * v, start, mid, l, r, value);
	update(2 * v + 1, mid + 1, end, l , r, value);
	tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

long long query(int v, int start, int end, int l, int r)
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
	long long q1 = query(2 * v, start, mid, l, r);
	long long q2 = query(2 * v + 1, mid + 1, end, l, r);
	return max(q1, q2);
}


int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m>>z;
	for(int i = 1; i <= z; i++) {
		int p, k, l;
		cin>>p>>k>>l;
		if(query(1,0,NTREE-1,p,k - 1) + l <= m) {
			update(1,0,NTREE-1,p,k-1,l);
			cout<<"T\n";
		}
		else cout<<"N\n";
	}
	return 0;
}
