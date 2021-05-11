#include<bits/stdc++.h>
#define N 3000001
using namespace std;

list< pair<int,int> > kmax; //para wartosc-indeks
list< pair<int,int> > kmin;
int tab[N], t, n;

void dodaj_max(int v,int odl)
{
	while(!kmax.empty() && kmax.back().first <= v)	kmax.pop_back();
	kmax.push_back({v,odl});
}

void dodaj_min(int v,int odl)
{
	while(!kmin.empty() && kmin.back().first >= v)	kmin.pop_back();
	kmin.push_back({v,odl});
}

int maks()
{
	if(!kmax.empty()) return (kmax.front()).first;
	return 0;
}

int mini()
{
	if(!kmin.empty()) return (kmin.front()).first;
	return 0;	
}

void usun_max(int odl)
{
	if( kmax.front().second==odl ) kmax.pop_front();
}

void usun_min(int odl)
{
	if( kmin.front().second==odl ) kmin.pop_front();
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>t>>n;
	for(int i = 1; i <= n; i++)	cin>>tab[i];
		
	int wynik = 1, idx = 1;
	for(int i = 1; i <= n; i++)
	{
		dodaj_max(tab[i],i);
		dodaj_min(tab[i],i);
		while(maks() - mini() > t) {
			usun_max(idx);
			usun_min(idx++);
		}
		wynik = max(wynik, i-idx+1);
	}
	cout<<wynik;
	return 0;
}
