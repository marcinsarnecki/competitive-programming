#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1e9 + 1;

#define NTREE 1048576
int tree[NTREE*2];

void update(int value,int l,int r)//dodaje 'value' na przedziale <l,r>
{
	l += NTREE;
	r += NTREE;
	if(l == r) {
		tree[l] += value;
		return;
	}
	tree[l] += value;
	tree[r] += value;
	while(r - l > 1) {
		if(l % 2 == 0) tree[l + 1] += value;
		if(r % 2 == 1) tree[r - 1] += value;
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

int main() { //drzewo przedzialowe (+,+) aktualizacja przedzialu, pytanie o punkt
	ios_base::sync_with_stdio(0);	
	return 0;
}
