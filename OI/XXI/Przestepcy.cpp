#include<bits/stdc++.h>
#define N 1000005
#define INF 1000000000
using namespace std;
int n, k, m, l, ans, ktory;
int c[N];//kolorkiii
int bitek[N], bajtek[N];// <1,m> <1,l> kolory kolejno odwiedzanych przez bitka i bajtka
int pos_bitek[N], pos_bajtek[N];//pozycja dobrego ustawienia drogi bitka bajtka
int best_left[N], best_right[N];//dla koloru najlepsza pozycja przedostatniego domu z lewej i z prawej
int next_right[N], next_left[N];//dla DANEJ POZYCJI gdzie jest kolejny taki sam kolor idac w prawo/lewo
int last[N];//pomocnicza nic nie znaczaca tablica
int pref[N];//sumy prefiksowe wystapien domu w ktorym ma dojsc do spotkania
vector<int> v;
void init()//wstepne ustawienie tablic next left right 
{
	for(int i = 1; i <= n; i++) {
		next_left[i] = INF;
		best_left[i] = INF;
		next_right[i] = -INF;
		best_right[i] = -INF;
		last[i] = INF;
	}	
	for(int i = n; i >= 1; i--) {//pozycja wie gdzie znajduje sie najblizej na prawo/lewo ten sam kolor co na tej pozycji o ktorej mowimy
		int kolor = c[i];
		next_right[i] = last[kolor];
		last[kolor] = i;
	}
	for(int i = 1; i <= n; i++) last[i] = -INF;
	for(int i = 1; i <= n; i++) {
		int kolor = c[i];
		next_left[i] = last[kolor];
		last[kolor] = i;
	}
	for(int i = 1; i <= n; i++) pref[i] = pref[i - 1] + (c[i] == bitek[l]);//sumy prefiksowe ostatniego domu zeby w O(1) wyznaczyc ile ich jest na przedziale
}

void wczytaj()//chyba wiadomo co ta funkcja robi 
{
	cin>>n>>k;
	for(int i = 1; i <= n; i++) cin>>c[i];
	cin>>l>>m;
	for(int i = 1; i <= l; i++) cin>>bitek[i];
	for(int i = 1; i <= m; i++) cin>>bajtek[i];
}

void ustaw()//wstepne ustawienie pierwszej dobrej drogi dla bitka i bajtka
{
	int idx = 1, i = 1;
	while(idx < l && i <= n)
	{
		if(bitek[idx] == c[i]) {
			pos_bitek[idx] = i;
			i++;
			idx++;
		}
		else {
			i++;
		}
	}
	for(;idx < l; idx++) pos_bitek[idx] = INF;
	idx = 1, i = n;
	while(idx < m && i >= 1) 
	{
		if(bajtek[idx] == c[i]) {
			pos_bajtek[idx] = i;
			i--;
			idx++;
		}
		else {
			i--;
		}
	}
	for(; idx < m; idx++) pos_bajtek[idx] = -INF;
}

int przedostatniBitek()
{
	return pos_bitek[l - 1];
}
int przedostatniBajtek()
{
	return pos_bajtek[m - 1];
}

void przesunBitek()
{
	pos_bitek[1] = next_right[pos_bitek[1]];
	for(int i = 2; i < l; i++) {
		while(pos_bitek[i] < pos_bitek[i - 1]) pos_bitek[i] = next_right[pos_bitek[i]];	
	}
}
void przesunBajtek()
{
	pos_bajtek[1] = next_left[pos_bajtek[1]];
	for(int i = 2; i < m; i++) {
		while(pos_bajtek[i] > pos_bajtek[i - 1]) {
			pos_bajtek[i] = next_left[pos_bajtek[i]];
		}
	}
}

void obliczBitek()
{
	if(l == 1) {
		for(int i = 1; i <= n - 1; i++)
		{
			int kolor = c[i];
			if(best_left[kolor] == INF) best_left[kolor] = i;
		}
		return;
	}
	for(int i = 1; i <= n - l; i++)
	{
		int kolor = c[i];
		if(pos_bitek[1] == i) przesunBitek();
		if(best_left[kolor] == INF) best_left[kolor] = przedostatniBitek();
	}
}
void obliczBajtek()
{
	if(m == 1) {
		for(int i = n; i >= 2; i--)
		{
			int kolor = c[i];
			if(best_right[kolor] == -INF) best_right[kolor] = i;
		}
		return;
	}
	for(int i = n; i >= m + 1; i--)
	{
		int kolor = c[i];
		if(pos_bajtek[1] == i) przesunBajtek();
		if(best_right[kolor] == -INF) best_right[kolor] = przedostatniBajtek();
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	init();
	ustaw();	
	obliczBitek();
	obliczBajtek();
	int left = N, right = 0;
	for(int kolor = 1; kolor <= k; kolor++) {
		if(best_right[kolor] - 1 < best_left[kolor] + 1) continue;
		left = min(left, best_left[kolor] + 1);
		right = max(right, best_right[kolor] - 1);
	}
	
	for(int i = left; i <= right; i++) if(c[i] == bitek[l]) v.push_back(i);
	cout<<v.size()<<"\n";
	for(auto u:v) cout<<u<<" ";
	return 0;
}
