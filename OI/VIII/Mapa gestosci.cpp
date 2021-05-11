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
#define N 251

int tab[N][N], sumpref[N][N], n, r;

void wej() {
    cin>>n>>r;
    rep(i,1,n)
        rep(j,1,n)
            cin>>tab[i][j];
}

void init() {
    rep(i,1,n)
        rep(j,1,n)
            sumpref[i][j] = sumpref[i-1][j] + sumpref[i][j-1] - sumpref[i-1][j-1] + tab[i][j];
}

int suma(int x1,int y1,int x2,int y2) {
	return sumpref[y2][x2]-sumpref[y2][x1-1]-sumpref[y1-1][x2]+sumpref[y1-1][x1-1];
}

void solve() {
    rep(i,1,n) {
		rep(j,1,n)
		{
			int x1 = j - r,
			    y1 = i - r,
			    x2 = j + r,
			    y2 = i + r;
			x1 = max(x1,1);
			y1 = max(y1,1);
			x2 = min(x2,n);
			y2 = min(y2,n);
			cout<<suma(x1,y1,x2,y2)<<" ";
		}
		cout<<"\n";
	}
}

int main() {
    ios_base::sync_with_stdio(0);
    wej();
    init();
    solve();
    return 0;
}
