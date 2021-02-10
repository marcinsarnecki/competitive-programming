#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;
#define N 2000007

ll pref[N];//sumy pref
ll dechy[N];//dechy, [i] -> <i,i+d-1>
int tab[N];//doly
int n, d;//dlugosc n i dechy
ll p;//ile my mamy workow z piachem
list<pair<ll,int> > l;//kmax
int wynik;

void dodaj(ll v,int idx)
{
	while(!l.empty() && l.back().first <= v) l.pop_back();
	l.push_back(make_pair(v, idx));
}

void usun(int idx)
{
	if(l.front().second == idx) l.pop_front();
}

ll maks()
{
	if(!l.empty()) return l.front().first;
	return 0;
}

ll suma(int a, int b) {
    return pref[b] - pref[a-1];
}

void wej() {
    cin>>n>>p>>d;
    rep(i,1,n) cin>>tab[i];
}

void init() {
    rep(i,1,n) pref[i] = pref[i-1] + tab[i];
    rep(i,1,n-d+1) dechy[i] = suma(i,i+d-1);
    wynik = d;
}

void solve() {
    int j = 1;
    dodaj(dechy[1],1);
    rep(i,d+1,n) {
        dodaj(dechy[i-d+1],i-d+1);
        while(maks() + p < suma(j,i)) 
            usun(j++);
        wynik = max(wynik, i - j + 1);
    }
    cout<<wynik;
}

int main()
{
	ios_base::sync_with_stdio(0);
	wej();
    	init();
   	solve();
	return 0;
}
