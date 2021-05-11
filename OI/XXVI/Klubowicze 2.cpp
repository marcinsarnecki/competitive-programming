#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define M 2000005
#define N 30
int pref0[N][M], pref1[N][M];
int useless[N];
int n, m, input[M];
int tab1[M], tab2[M];
ll ans;

bool przedzial(int a, int b) { //czy przedzial <a,b> jest dobry 
    if(a == b) {
        rep(i,0,n-1)
            if(useless[i] == 0) //jesli jakis poglad nie jest bezuzytczny to znaczy ze sie nie da, poniewaz przedzial jest dlugosci 1 a potrzeba w nim obu odpowiedzi na dany poglad
                return false;
    }
    if(a < b) { //normalny przedzial
        rep(i,0,n-1) {
            if(useless[i]) //bezuzyteczny poglad - nie trzeba go rozpatrywac
                continue;
            if(pref0[i][b] - pref0[i][a - 1] == 0) return false;
			if(pref1[i][b] - pref1[i][a - 1] == 0) return false;
        }
    }
    if(a > b) { //przedzial przechodzacy przez koniec na poczatek (okragly stol)
        rep(i,0,n-1) {
            if(useless[i]) //bezuzyteczny poglad - nie trzeba go rozpatrywac
                continue;
            if(pref0[i][m] - pref0[i][a - 1] + pref0[i][b] == 0) return false;
			if(pref1[i][m] - pref1[i][a - 1] + pref1[i][b] == 0) return false;
        }
    }
    return true;
}

void wczytaj() {
    cin>>n>>m;
    rep(j,1,m) 
        cin>>input[j];
}

void init() {
    rep(j,1,m) {
        int x = input[j];
        rep(i,0,n-1) {
            if(x % 2 == 1) {
		pref1[i][j] = pref1[i][j - 1] + 1;
		pref0[i][j] = pref0[i][j - 1];
	    }
	    else {
		pref1[i][j] = pref1[i][j - 1];
		pref0[i][j] = pref0[i][j - 1] + 1;
	    }
	    x /= 2;
        }
    }
    rep(i,0,n-1)
        if(pref0[i][m] == m || pref1[i][m] == m) //jesli wszedzie w wierszu sa 1 albo 0 to ten wiersz jest bezuzyteczny
            useless[i] = true;
}

int dystans(int a, int b) //dystans zgodny z okraglym stolem
{
	if(a <= b) return b - a + 1;
	return b + m - a + 1;
}

void oblicz1() {
    int p = 1, k = 2;
	for(; p <= m; p++) {
		while(przedzial(p,k) == 0) {
			k++;
			if(k > m) k = 1;
		}
		tab1[p] = k;//idac w prawa strone pierwsze miejsce przy ktorym przedzial <p,k> jest dobry
	}
}

void oblicz2() {
    int p = m, k = m-1;
    for(; p >= 1; p--) {
        while(przedzial(k,p) == 0) {
            k--;
            if(k < 1) k = m;
        }
        tab2[p] = k;//idac w lewa strone pierwsze miejsce przy ktorym przedzial <k,p> jest dobry
    }
}

void solve() {
    rep(j,1,m) {
        int p1 = j, k1 = tab1[j];
        int k2 = (j == 1) ? m : j-1, p2 = tab2[k2];
        if(dystans(p2,k2) + dystans(p1,k1) > m)
            continue;
        ans += m - (dystans(p2,k2) + dystans(p1,k1)) + 1;
    }
    cout<<ans / 2;//wyszlo dwa razy za duzo
}

int main()
{
    ios_base::sync_with_stdio(0);
    wczytaj();
    init();
    oblicz1();
    oblicz2();
    solve();
    return 0;
}
