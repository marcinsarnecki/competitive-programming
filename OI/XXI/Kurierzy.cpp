#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 500001
#define NTREE 524288
#define INF 1000000000

pii tree[2*NTREE]; // para <kandydat-ile>
int tab[N], n, m;
pii zap[N];

vector<int> wystapienia[N]; //kazda liczba posiada vector z pozycjami na ktorych sie znajduje

pii scal(pii a, pii b)//kandydat na lidera z dwoch wierzcholkow
{
	if (a.first == b.first) return {a.f, a.s + b.s};
	if (a.second < b.second) swap(a, b);
	return {a.first, a.second - b.second};
}

int query(int l, int p)
{
	p += NTREE;
	l += NTREE;
	if (l == p) return tree[l].first;
	pii ans = scal(tree[l], tree[p]);
	while (p - l > 1) {
		if (l % 2 == 0) ans = scal(ans, tree[l + 1]);
		if (p % 2 == 1) ans = scal(ans, tree[p - 1]);
		l /= 2;
		p /= 2;
	}
	return ans.f;
}

void update(int pos, pii v) {
    pos += NTREE;
    tree[pos] = v;
    pos /= 2;
    while(pos) {
        tree[pos] = scal(tree[2*pos], tree[2*pos+1]);
        pos /= 2;
    }
}

int ilosc(int v, int a, int b) { //ile v pomiedzy <l,r>
	return upper_bound(wystapienia[v].begin(),wystapienia[v].end(),b) - lower_bound(wystapienia[v].begin(),wystapienia[v].end(),a);
}

int main()
{
	ios_base::sync_with_stdio(0);
    cin>>n>>m;
	rep(i,1,n) {
		cin>>tab[i];
		update(i, {tab[i], 1});
		wystapienia[tab[i]].pb(i);
	}

	rep(i,1,n)
        wystapienia[tab[i]].pb(INF);

	rep(i,1,m) {
		int a, b;
		cin>>a>>b;
		zap[i] = {a,b};
	}

	rep(i,1,m) {
		int l = zap[i].f, r = zap[i].s;//przedzial
		int k = query(l,r); // kandydat na lidera
		int ile = ilosc(k,l,r); 
		if(ile > (r-l+1)/2) 
            cout<<k<<"\n";
		else 
            cout<<"0\n";
	}
	return 0;
}
