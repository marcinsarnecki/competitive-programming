#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = (ll) 1000000 * 1000000 * 1000000 + 1;// o jeden wiecej niz maksymalna wartosc w tym zadaniu

#define SIZE 205

int s, m, q;
ll dp[SIZE][SIZE][SIZE]; // dp[i][r][d] - ilosc liczb dlugosci i, reszcie r przy dzieleniu przez m, sumie cyfr d
ll potegi[SIZE]; // 10^i % m
ll all[SIZE];//wszystkie liczby dlugosci i, ktore pasujace (suma s, reszta z dzielenia 0)

void add(ll &a, ll b) {//bezpieczne dodawanie, zeby sie tam nie przekrecilo
	a += b;
	if(a > INF)
		a = INF;
}

void dynamik() {
	potegi[0] = 1;
	rep(i,1,200)
		potegi[i] = (potegi[i-1] * 10) % m;
	dp[0][0][0] = 1; //pusta liczba
	rep(i,1,200)
		rep(r,0,m-1)
			rep(d,0,s)
				rep(c,0,9) {
					//probujemy zbudowac liczbe postaci c XYZ (c * potegi[i-1]) + XYZ
					// c XYZ
					if(c > d)							// zeby obliczyc dp[i][r][d] doklejajac c do XYZ (powstanie cXYZ)
						continue;						// potrzebujemy ilosci liczb XYZ o sumie d-c oraz o
					int newsum = d - c;		// takiej reszcie z dzielenia, zeby ta reszta + c*potegi[i] dalo r mod m
					int newr = ((r - (c * potegi[i-1]) % m) + m ) % m;
					add(dp[i][r][d], dp[i-1][newr][newsum]);
				}
	rep(i,1,200)
		all[i] = dp[i][0][s];
}

void odtworz(ll k) {
	if(dp[200][0][s] < k) { //jesli nie ma tyle liczb to NIE
		cout<<"NIE\n";
		return;
	}
	vector<int> liczba;
	int currentr = 0;		//aktualna reszta z dzielenia przez m
	int currentsum = s;		//aktualna suma cyfr
	int len;//trzeba znalezc miejsce odkad odtwarzamy liczbe (czyli po prostu jej dlugosc)
	for(len = 1; len <= 200; len++)
		if(dp[len][0][s] >= k) //jesli jakies miejsce wystarcza to przerywamy
			break;
	repv(i,len,1) {
		rep(c,0,9) {			//znajdowanie cyferki					              //sprawdzamy ile jest liczb cXYZ
			int newsum = currentsum - c;								                //jesli k <= to znaczy ze wynik miesci sie
			int newr = ((currentr - (c * potegi[i-1]) % m) + m ) % m; 	//w zakresie liczb cXYZ i trzeba wypisac c i leciec dalej
			if(dp[i-1][newr][newsum] < k)								                //jesli k > to wtedy trzeba odjac od k i liczyc dalej			
				k -= dp[i-1][newr][newsum];
			else {
				liczba.pb(c);
				currentr = newr;
				currentsum = newsum;
				break;
			}
		}
	}
	for(auto c: liczba)
		cout<<c;
	cout<<endl;
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>s>>m>>q;
	dynamik();
	while(q--) {
		ll k;
		cin>>k;
		odtworz(k);
	}
	return 0;
}
