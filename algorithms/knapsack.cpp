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

#define N 101
#define MAXW 1001

int waga[N], wartosc[N];
int dp[N][MAXW];
int n, W;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>W;
	rep(i,1,n) 
		cin>>wartosc[i]>>waga[i];
	rep(i,1,n)	// dp[i][j] oznacza najwieksza wartosc jaka mozemy uzyskac dla wagi 'j' uzywajac 'i' przedmiotow
		rep(j,1,W) {
			if(waga[i] > j) //przedmiot jest za duzy
				dp[i][j] = dp[i-1][j];
			else
				dp[i][j] = max(dp[i-1][j], dp[i-1][j-waga[i]] + wartosc[i]);
		}
	
	int ans = dp[n][W];
	cout<<"Maksymalna wartosc: "<<ans<<"\n";
	for(int i = n; i >= 1 && ans > 0; i--) { //kod odtwarzajacy ktore przedmioty zostaly uzyte do dp[n][W], ans to aktualna wartosc, W waga
		if(ans == dp[i-1][W]) //to samo mozna uzyskac bez itego przedmiotu wiec nie bierzemy go
			continue;
		else {	//ity przedmiot zostal uzyty
			cout<<"przedmiot nr "<<i<<": "<<wartosc[i]<<" "<<waga[i]<<"\n";
			ans -= 	wartosc[i];//aktualizacja aktualnej wartosci i wagi
			W 	-= 	waga[i];
		}
	}
	return 0;
}
