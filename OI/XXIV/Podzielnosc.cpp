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
#define Q 100001

int B, q, idx, a[N];
ll sum, last, g, zap[Q];

struct cyfra {
    int i;//jaka cyfra
    ll p, k;// poczatek, koniec gdzie ona jest w wynikowej liczbie
}liczba[N];

void wczytaj() {
    cin>>B>>q;
    rep(i,0,B-1)
        cin>>a[i];
    rep(i,1,q)
        cin>>zap[i];
}

void init() {
    rep(i,0,B-1)
        sum += (ll)a[i] * i;
    ll rest = sum % (B-1);
    if(rest != 0)
        a[rest]--;//korekta zeby bylo podzielne przez b-1
    rep(i,0,B-1) {
        if(a[i] > 0) {
            liczba[idx].i = i; //po kolei wszystkie cyfry tej liczby
            liczba[idx].p = g;
            g += a[i] - 1;
            liczba[idx++].k = g++;
        }
    }
    idx--;
    last = liczba[idx].k; 
}

ll query(ll pos) {
    if(pos > last)
        return -1;
    ll l = 0, r = idx, mid;
    while(l <= r) {
        mid = (l + r) / 2;
        if(pos <= liczba[mid].k)
            r = mid-1;
        else
            l = mid + 1;
    }
    return liczba[r+1].i;
}

void solve() {
    rep(i,1,q)
        cout<<query(zap[i])<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
    	init();
    	solve();
	return 0;
}
