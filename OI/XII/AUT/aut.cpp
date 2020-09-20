#include<bits/stdc++.h>
#define NTREE 131072
using namespace std;
int sdx, n, m, k, tree[NTREE * 2];//max,max przedzial-punkt
map<int,int> mapa;//skalowanie
int skaluj(int pos)
{
	return mapa[pos];
}
struct pkt
{
	int x, y, ile;
	pkt(int a, int b, int c) 
	{
		x = a, y = b, ile = c;
	};
	pkt()
	{
		x = y = ile = 0;
	}
}q[100001];

void insert(int pos, int value) 
{
	pos += NTREE;
	tree[pos] = max(tree[pos], value);
	pos /= 2;
	while(pos) {
		tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
		pos /= 2;
	}
}

int query(int l, int r)
{
	l += NTREE, r += NTREE;
	int ans = tree[l];
	if(r > l) ans = max(ans, tree[r]);
	while(r - l > 1) {
		if(l % 2 == 0) ans = max(ans, tree[l + 1]);
		if(r % 2 == 1) ans = max(ans, tree[r - 1]);
		l /= 2, r /= 2;
	}
	return ans;
}

class compare
{
	public:
		bool operator()(const pkt& pkt1, const pkt& pkt2) {
			if(pkt1.y == pkt2.y) return pkt1.x < pkt2.x;
			return pkt1.y < pkt2.y;
		}
};

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i = 1; i <= k; i++) {
		int a, b, c;
		cin>>a>>b>>c;
		mapa[a] = 1;
		q[i] = pkt(a, b, c);
	}
	for(auto &it: mapa) {//skalowanie tylko po x, po y nie jest potrzebne, y sa ulozone rosnaco i to wszystko
		it.second = ++sdx;
	}
	sort(q + 1, q + 1 + k, compare());
	for(int i = 1; i <= k; i++) {
		
		int x = skaluj(q[i].x);//bierzemy 'x' z zapytania i skalujemy
		int ans = query(1, x);
		insert(x, ans + q[i].ile);
	}
	cout<<query(1,k);
	return 0;
}
