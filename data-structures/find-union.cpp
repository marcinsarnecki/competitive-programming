#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1001

int n;
vector<int> p(N), r(N, 1);

int find(int v) {
	if(v == p[v]) 
		return v;
	return p[v] = find(p[v]);
}

bool union_sets(int v, int u) {
	v = find(v), u = find(u);
	if(v == u)
		return false;
	if(r[u] < r[v])
		swap(u, v);
	r[u] += r[v];
	p[v] = u;
	return true;
}

int main()
{
	ios_base::sync_with_stdio(0);
	rep(i,1,n)
		p[i] = i;
	return 0;
}
