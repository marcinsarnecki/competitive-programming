#include<bits/stdc++.h>
#define N 1000001
using namespace std;

int x[N], n, q;
long long pref[N];
vector<int> min_pref, max_suf;

void solve(int k)
{
	for(int i = 1; i <= n; i++) pref[i] = pref[i-1] + (x[i] - k);//samo ustawianie pref i czyszczenie dwoch pomocniczych vectorow, izi
	min_pref.clear();
	max_suf.clear();
	
	//obserwacja: chcemy takie l i r, zeby pref[r] - pref[l] >= 0 i zeby l i r byly jak najdalej, minima pref i maxima suf
	//jesli pref[i] <= pref[j] oraz i < j to tamto pref[j] jest nieoptymalne!! analogicznie z suf
	
	min_pref.push_back(0);//corner case: z lewej strony nie bierzemy nic, indeks = 0
	long long akt_min = 0;
	for(int i = 1; i <= n; i++) {
		if(pref[i] < akt_min) {
			akt_min = pref[i];
			min_pref.push_back(i);//indeksiki
		}
	}
	
	max_suf.push_back(n);
	long long akt_max = pref[n];
	for(int i = n - 1; i >= 1; i--) {
		if(pref[i] > akt_max) {
			akt_max = pref[i];
			max_suf.push_back(i);
		}
	}
	reverse(max_suf.begin(), max_suf.end());
	
	int j = 0, wynik = 0;
	for(int i = 0; i < min_pref.size(); i++) {
		while(j < max_suf.size() - 1 && pref[max_suf[j + 1]] - pref[min_pref[i]] >= 0) j++;//czy mozemy sie wgl ruszyc z j + warunek
		if(pref[max_suf[j]] - pref[min_pref[i]] >= 0) wynik = max(wynik, max_suf[j] - min_pref[i]);//maxujemy wynik
	}
	cout<<wynik<<" ";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>q;
	for(int i = 1; i <= n; i++) cin>>x[i];
	for(int i = 1; i <= q; i++) {
		int k;
		cin>>k;
		solve(k);
	}
	return 0;
}
