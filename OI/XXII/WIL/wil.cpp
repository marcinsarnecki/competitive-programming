#include<bits/stdc++.h>
#define N 2000007
using namespace std;

long long pref[N];//sumy pref
long long dechy[N];//dechy, [i] -> <i,i+d-1>
int tab[N];//doly
int n, d;//dlugosc n i dechy
long long p;//ile my mamy workow z piachem
list<pair<long long,int> > l;//kmax
int wynik;

void dodaj(long long v,int idx)
{
	while(!l.empty() && l.back().first <= v) l.pop_back();
	l.push_back(make_pair(v, idx));
}

void usun(int idx)
{
	if(l.front().second == idx) l.pop_front();
}

long long maks()
{
	if(!l.empty()) return l.front().first;
	return 1000000000000000000ll;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>p>>d;
	wynik = d;
	for(int i = 1; i <= n; i++) cin>>tab[i];
	for(int i = 1; i <= n; i++) pref[i] = pref[i-1] + tab[i];
	for(int i = 1; i <= n - d + 1; i++) dechy[i] = pref[i + d - 1] - pref[i - 1];
	
	int i = 1, j = d;
	dodaj(dechy[1], 1);
	
	while(1)
	{
		if(j >= n) break;// >= bo jesli j = n to juz nie ma po co bo w poprzednim wynik zostal zmaksowany, jesli i wyjdzie za daleko i decha pokryje calosc to tam jest return +inf w kolejce
		
		if(pref[j + 1] - pref[i - 1] - max(maks(), dechy[j - d + 2]) <= p)
		{
			dodaj(dechy[j - d + 2], j - d + 2);
			j++;
		}
		else
		{
			usun(i);
			i++;
		}
		wynik = max(wynik, j - i + 1);
	}
	cout<<wynik;
	return 0;
}
