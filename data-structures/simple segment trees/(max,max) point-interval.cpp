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
int tree[NTREE*2];

int query(int p, int k) {//pytanie o max na przedziale <a,b>
	p += NTREE, k += NTREE;
	if(p == k)
		return tree[p];
	int ans = max(tree[p], tree[k]);
	while(k - p > 1) {
		if(p % 2 == 0) ans = max(ans, tree[p + 1]);
		if(k % 2 == 1) ans = max(ans, tree[k - 1]);
		p /= 2;
		k /= 2;
	}
	return ans;
}

void update(int value, int pos) {//maksuje pozycje 'pos' wartoscia 'value'
	pos += NTREE;
	while(pos) {
		tree[pos] = max(tree[pos], value);
		pos /= 2;
	}
}

int main() { //drzewo przedzialowe (max,max) aktualizacja punktu, pytanie o przedzial
	ios_base::sync_with_stdio(0);	
	return 0;
}
