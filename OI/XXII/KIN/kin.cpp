#include<bits/stdc++.h>
#define N 1000001
#define NTREE 1048576
#define f first
#define s second
#define INF 1000000000
using namespace std;
typedef long long ll;
pair<ll,ll> tree[2 * NTREE];//max lewo, suma
int tab[N], c[N], odkad[N], n, m;
long long ans;
vector<int> pos[N];//pozycje [] filmu

void update(int i)//update wezla i
{
	tree[i].s = tree[2*i].s + tree[2*i+1].s;
	tree[i].f = max(tree[2*i].f, tree[2*i].s);
	tree[i].f = max(tree[i].f, tree[2*i].s + tree[2*i+1].f);
	tree[i].f = max(tree[i].f, tree[i].s);
}

void setv(int pos, int value)//ustawia value na pozycji pos
{
	pos += NTREE;
	tree[pos] = {value,value};
	pos /= 2;
	while(pos) {
		update(pos);
		pos /= 2;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= n; i++) {
		cin>>tab[i];
		pos[tab[i]].push_back(i);
	}
	for(int i = 1; i <= m; i++) cin>>c[i];
	for(int i = 1; i <= m; i++) {
		pos[i].push_back(INF);
		pos[i].push_back(INF);
		pos[i].push_back(INF);
		int v = i;
		if(pos[v][0] != INF) setv(pos[v][0], c[v]);
		if(pos[v][1] != INF) setv(pos[v][1], -c[v]);
	}
	ans = max(ans, tree[1].f);
	for(int i = 1; i <= n; i++) {
		int v = tab[i], idx = odkad[v];
		setv(i, 0);
		if(pos[v][idx + 1] != INF) setv(pos[v][idx+1], c[v]);
		if(pos[v][idx + 2] != INF) setv(pos[v][idx+2], -c[v]);
		odkad[v]++;
		ans = max(ans, tree[1].f);
	}
	cout<<ans;
	return 0;
}
