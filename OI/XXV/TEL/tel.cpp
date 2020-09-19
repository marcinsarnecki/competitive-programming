#include<bits/stdc++.h> //drzewo update ciag arytmetyczny, query suma
#define NTREE 524288
using namespace std;

long long tree[NTREE * 2], lazy_a[NTREE * 2], lazy_b[NTREE * 2];
int n, m;

struct zap
{
	int l,x,r,s,a;
	zap(int a1,int a2,int a3,int a4,int a5) {
		l = a1, x = a2, r = a3, s = a4, a = a5;
	}
	zap() {
		l = x = r = s = a = 0;
	}
}maszt[300001];

long long ciag(int p, int k, int a, int b)
{
	return (1ll*2*b + (1ll*k - p)*a) * (1ll*k - p + 1) / 2;
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
		tree[v] += ciag(start, end, a, b);//WAZNE MIEJSCE, V CALKOWICIE W ZAKRESIE L,R MA INNE B PRZY START NIZ B PRZY L 
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

long long query(int v, int start, int end, int l, int r)
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
	
	long long q1 = query(v * 2, start, mid, l, r);
	long long q2 = query(v * 2 + 1, mid + 1, end, l, r);
	return q1 + q2;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		char z;
		cin>>z;
		if(z == 'P') {
			int x, s, a;
			cin>>x>>s>>a;
			int d = s / a;
			int l = x - d, r = x + d;
			l = max(1, l);
			r = min(n, r);
			update(1,0,NTREE-1,x,x,0,s);
			if(l <= x-1) update(1,0,NTREE-1,l,x-1,a,s-(x-l)*a);
			if(r >= x+1) update(1,0,NTREE-1,x+1,r,-a,s-a);
			maszt[x] = zap(l,x,r,s,a);
		}
		if(z == 'U') {
			int x;
			cin>>x;
			int l = maszt[x].l, r = maszt[x].r, s = maszt[x].s, a = maszt[x].a;
			update(1,0,NTREE-1,x,x,0,-s);
			if(l <= x-1) update(1,0,NTREE-1,l,x-1,-a,-s+(x-l)*a);
			if(r >= x+1) update(1,0,NTREE-1,x+1,r,a,a-s);
			maszt[x] = zap(0,0,0,0,0);
		}
		if(z == 'Z') {
			int p, k;
			cin>>p>>k;
			cout<<query(1,0,NTREE-1,p,k) / (k - p + 1)<<"\n";
		}
	}
	return 0;
}
