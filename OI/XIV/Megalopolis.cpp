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

#define N 250001
#define NTREE 262144
int n, m;
vector<int> graf[N];
int preorder[N], postorder[N], idx, dist[N];
int tree[2*NTREE];

void update(int l,int r)
{
	l += NTREE;
	r += NTREE;
	if(l == r) {
		tree[l] ++;
		return;
	}
	tree[l] ++;
	tree[r] ++;
	while(r - l > 1) {
		if(l % 2 == 0) tree[l + 1] ++;
		if(r % 2 == 1) tree[r - 1] ++;
		l /= 2;
		r /= 2;
	}
}
int query(int pos)
{
	pos += NTREE;
	int sum = 0;
	while(pos) {
		sum += tree[pos];
		pos /= 2;
	}
	return sum;
}

void dfs(int v, int d) {
	idx++;
	preorder[v] = idx;
	dist[v] = d;
	for(auto u: graf[v])
		dfs(u, d + 1);
	postorder[v] = idx;
}

void wej() {
	cin>>n;
	rep(i,1,n-1) {
		int a, b;
		cin>>a>>b;
		if(a > b) swap(a,b);
		graf[a].pb(b);
		//graf[b].pb[a];
	}
	dfs(1,0);
//	rep(i,1,n) cout<<"v="<<i<<" pre="<<preorder[i]<<" post="<<postorder[i]<<"\n";
	cin>>m;
	rep(i,1,n + m - 1) {
		char z;
		cin>>z;
		if(z == 'A') {
			int a, b;
			cin>>a>>b;
			if(a > b) swap(a,b);
			update(preorder[b],postorder[b]);	
		}
		if(z == 'W') {
			int v;
			cin>>v;//query
			cout<<dist[v] - query(preorder[v])<<"\n";
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	return 0;
}
