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

void update(int l, int r, int value) //maksowanie przedzialu wartoscia value
{
	if(l > r) return;
	l += NTREE;
	r += NTREE;
	tree[l] = max(tree[l], value);
	tree[r] = max(tree[r], value);
	while(r - l > 1) {
		if(l % 2 == 0) tree[l + 1] = max(tree[l + 1], value);
		if(r % 2 == 1) tree[r - 1] = max(tree[r - 1], value);
		l /= 2;
		r /= 2;
	}
}

int query(int pos)//pytanie o punkt
{
	int ans = 0;
	pos += NTREE;
	while(pos) {
		ans = max(ans, tree[pos]);
		pos /= 2;
	}
	return ans;
}

int main() { //drzewo przedzialowe (max,max) aktualizacja przedzialu, pytanie o punkt
	ios_base::sync_with_stdio(0);	
	return 0;
}
