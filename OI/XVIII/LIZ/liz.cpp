#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000001
int tab[N], zap[N], sum;

pii ans[2 * N];
int pom, n, m;
int lw, rw;//pierwsza wanilia z lewej i prawej

void wczytaj() {
	cin>>n>>m;
    rep(i,1,n) {
        char z;
        cin>>z;
        if(z == 'W')
            tab[i] = 1;
        else
            tab[i] = 2;
        sum += tab[i];
    }
    rep(i,1,m)
        cin>>zap[i];
}

void oblicz(pii pos, int s) {
    if(s <= 0)
        return;
    ans[s] = pos;
    int l = pos.f, r = pos.s;
    if(tab[l] == 2)
        oblicz({l+1,r},s-2);
    else if(tab[r] == 2)
        oblicz({l,r-1},s-2);
    else
        oblicz({l+1,r-1},s-2);
}

void solve() {
    rep(i,1,n) 
        if(tab[i] == 1) {
            lw = i;
            break;
        }
    repv(i,n,1) 
        if(tab[i] == 1) {
            rw = i;
            break;
        }
    ans[sum] = {1,n};
    oblicz({1,n}, sum);
    if(lw != 0) {
        if(lw-1 < n-rw)
            oblicz({lw+1,n}, sum - (2 * (lw-1)) - 1);
        else
            oblicz({1,rw-1}, sum - (2 * (n-rw)) - 1);
    }
    rep(i,1,m)
        if(ans[zap[i]].f == 0)
            cout<<"NIE\n";
        else
            cout<<ans[zap[i]].f<<" "<<ans[zap[i]].s<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
    solve();
	return 0;
}
