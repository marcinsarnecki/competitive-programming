#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1001

int n, m, a, b;
int tab[N][N];
vector<pii> p;

void solve() {
    cin>>n>>m>>a>>b;
    p.clear();
    rep(i,1,n) {
        string s;
        cin>>s;
        rep(j,1,m)
            if(s[j-1] == 'x')
                tab[i][j] = 1;
            else
                tab[i][j] = 0;
     }
    pii pierwsze = {0,0};
    rep(i,1,a)
        rep(j,1,b) {
            char z;
            cin>>z;
            if(z == 'x') {
                p.pb({i,j});
                if(pierwsze.f == 0 || pierwsze.s == 0)
                    pierwsze = {i,j};
            }
        }
    for(auto &it: p)
        it.f -= pierwsze.f, it.s -= pierwsze.s;
    rep(i,1,n)
        rep(j,1,m) { 
            if(tab[i][j]) {
                for(auto it: p) {
                    int ii = i + it.f, jj = j + it.s;
                    if(ii > n || jj > m || tab[ii][jj] == 0) { //poza plansza albo dwa razy w to samo miejsce
                        cout<<"NIE\n"; 
                        return;
                    }
                    else
                        tab[ii][jj] = 0;
                }
            }
        }
    rep(i,1,n)
        rep(j,1,m) 
            if(tab[i][j]) {
                cout<<"NIE\n";
                return;
            }
    cout<<"TAK\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin>>t;
    rep(i,1,t)
        solve();
	return 0;
}
