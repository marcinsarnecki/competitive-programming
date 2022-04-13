#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define NTREE 131072
#define N 100001

int idx, n, m, k, tree[NTREE * 2];//max,max przedzial-punkt
map<int,int> mapa;//skalowanie

struct pkt
{
	int x, y, ile;
	pkt(int a, int b, int c) 
	{
		x = a, y = b, ile = c;
	};
	pkt() {x = y = ile = 0;}
}q[N];

void update(int value, int pos) {//maksuje pozycje 'pos' wartoscia 'value'
	pos += NTREE;
	while(pos) {
		tree[pos] = max(tree[pos], value);
		pos /= 2;
	}
}

int query(int l, int r) {
	l += NTREE, r += NTREE;
	int ans = max(tree[l], tree[r]);
	while(r - l > 1) {
		if(l % 2 == 0) ans = max(ans, tree[l + 1]);
		if(r % 2 == 1) ans = max(ans, tree[r - 1]);
		l /= 2, r /= 2;
	}
	return ans;
}

bool cmp(const pkt& pkt1, const pkt& pkt2) {//rosnaco po y, rosnaco po x
	if(pkt1.y == pkt2.y)
		return pkt1.x < pkt2.x;
	return pkt1.y < pkt2.y;
}

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
	for(auto &it: mapa) //skalowanie tylko po x
		it.second = ++idx;
	sort(q + 1, q + 1 + k, cmp);
	for(int i = 1; i <= k; i++) {
		int x = mapa[q[i].x]; //bierzemy 'x' z danego miejsca i skalujemy
		int best = query(1, x) + q[i].ile; //najlepszy dostepny poprzedni wynik + ile osob w danym miejscu
		update(best, x); //update punktu x (przeskalownego) na drzewie przedzialowym
	}
	cout<<query(1,k);
	return 0;
}
