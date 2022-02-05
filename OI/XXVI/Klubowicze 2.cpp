#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define M 2000001
#define N 30
int pref[N][M], useless[N];
int n, m, members[M], r[M], l[M];
ll ans;

bool check(int a, int b) { //czy przedzial <a,b> jest dobry 
    if(a == b) 
        return false;
    if(a < b) { //normalny przedzial
        rep(i,0,n-1) {
            if(useless[i]) //bezuzyteczny poglad - nie trzeba go rozpatrywac
                continue;
            int sum = pref[i][b] - pref[i][a - 1];
            if(sum == 0 || sum == b - a + 1)
				return false;
        }
    }
    if(a > b) { //przedzial przechodzacy przez koniec na poczatek (okragly stol)
        rep(i,0,n-1) {
            if(useless[i]) //bezuzyteczny poglad - nie trzeba go rozpatrywac
                continue;
            int sum = pref[i][m] - pref[i][a - 1] + pref[i][b];
            if(sum == 0 || sum == m - a + 1 + b)
				return false;
        }
    }
    return true;
}

void input() {
    cin>>n>>m;
    rep(j,1,m) 
        cin>>members[j];
}

void init() {
    rep(j,1,m) {
        int x = members[j];
        rep(i,0,n-1) {
            pref[i][j] = pref[i][j-1] + (x % 2);
			x /= 2;
        }
    }
    rep(i,0,n-1)
        if(pref[i][m] == m || pref[i][m] == 0) //jesli wszedzie w wierszu sa 1 albo 0 to ten wiersz jest bezuzyteczny
            useless[i] = true;
}

int distance(int a, int b) {//dystans zgodny z okraglym stolem
	if(a <= b) return b - a + 1;
	return b + m - a + 1;
}

void solve() {
	int k = 1;
	rep(j,1,m) {
		while(!check(j, k)) 
			k == m ? k = 1 : k++;
		r[j] = k;
	}
	k = m;
	repv(j,m,1) {
		while(!check(k, j))
			k == 1 ? k = m : k--;
		l[j] = k;
	}
	rep(j,1,m) {
		k = r[j];
		int k2 = (j == 1) ? m : j-1, j2 = l[k2]; 
		if(distance(j2, k2) + distance(j, k) > m)
			continue;
		ans += distance(k, j2) - 1;
	}
    cout<<ans / 2;
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	init();
	solve();
	return 0;
}
