#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 201
#define MAX_C 20005
#define INF 1000000000

int n, kwota, b[N], c[N], dp[N][MAX_C], ile[N][MAX_C]; 
list<pii> kmax;// <k,dp>

void dodaj(int k, int value) {
	while(kmax.size() && value - kmax.back().s <= k - kmax.back().f) kmax.pop_back();	//jesli aktualne miejsce jest lepsze od tych poprzednich (jest tak kiedy roznica w dynamiku jest <= roznicy w indeksach k)
	kmax.push_back({k,value});															//(wtedy dla kolejnych k oplaca sie wziac nasze miejsce niz siegac dalej)
}

void usun(int k) {
	if(kmax.front().f == k) kmax.pop_front();
}

void czystka() {
	while(kmax.size()) kmax.pop_back();
}

pii best() {
	return kmax.front();
}

void wczytaj() {
	cin>>n;
	rep(i,1,n)
		cin>>b[i];
	rep(i,1,n)
		cin>>c[i];
	cin>>kwota;
}

void solve() {
	rep(i,0,n)
		rep(j,1,kwota)
			dp[i][j] = INF;
	rep(i,1,n) 
		for(int start = 0; start < b[i]; start++) {
			czystka();
			for(int k = 0; start + k * b[i] <= kwota; k++) {
				dodaj(k, dp[i-1][start + k * b[i]]);
				int bestVal = best().s, bestK = best().f;//kolejka zwraca nam miejsce na ktore najbardziej oplaca sie spojrzec przy polepszaniu wyniku
				dp[i][start + k * b[i]] = bestVal + k - bestK;
				ile[i][start + k * b[i]] = k - bestK;
				usun(k - c[i]);//usuwamy miejsce do ktorego nie mozemy sie juz odwolac
			}
		}

	vector<int> wyniki;
	int current = kwota;
	repv(i,n,1) {
		wyniki.pb(ile[i][current]); //odtwarzanie wyniku
		current -= ile[i][current] * b[i];
	}
	reverse(wyniki.begin(), wyniki.end());

	cout<<dp[n][kwota]<<"\n";
	for(auto it: wyniki)
		cout<<it<<" ";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
