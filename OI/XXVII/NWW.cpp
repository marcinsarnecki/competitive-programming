#include<bits/stdc++.h>

using namespace std;

map<long long,pair<int,int>> mapa;
int zakres[]{0,0,0,0,49488,7512,2215,930,504,280,216,140,110,88,65,54,51,40,39,34,33,25};//do [21]

long long rpm(long long a, long long b)
{
	long long ans = 0;
	while(b > 0)
	{
		if(b % 2 == 1) ans += a;
		a<<=1;
		b>>=1;
		if(ans > 1e18 || (a > 1e18 && b > 0)) return 0;
	}
	return ans;
}

long long nww(long long a,long long b)
{
	if(a == 0 || b == 0) return 0;
	a /= __gcd(a,b);
	return rpm(a,b);
}

long long przedzial(long long a, long long b)
{
	long long ans = a;
	for(int i = a + 1; i <= b; i++) ans = nww(ans, (long long)i);
	return ans;
}

void ans(long long M)
{
	long long l = 0, r = 0, a, b;//wynikowy przedzial
	
	a = floor(sqrt(M)), b = a + 1;
	if(a * b == M) {//proba ab
		l = a, r = b;
	}
	
	a = ceil(cbrt(2*M)) - 1, b = a + 2;
	if(przedzial(a,b) == M) {//proba abc/2
		l = a, r = b;
	}
	
	a = ceil(cbrt(M)) - 1, b = a + 2;
	if(przedzial(a,b) == M) {//proba abc
		l = a, r = b;
	}
	
	if(mapa.count(M) != 0) {
		pair<int,int> current = mapa[M];
		if(l == 0) 	l = current.first, r = current.second;
		else if(current.first < l || (current.first == l && current.second < r)) l = current.first, r = current.second;
	}
	if(l == 0) cout<<"NIE\n";
	else cout<<l<<" "<<r<<"\n";
}

void init()
{
	int a, b;
	for(int start = 4; start <= 21; start++)
	{
		a = 1, b = start;
		while(a <= zakres[start]) {
			long long wynik = przedzial(a,b);
			if(wynik == 0) //useless przedzial
			{
				a++, b++;
				continue;
			}
			if(mapa.count(wynik) == 0) mapa[wynik] = {a,b};//jesli liczba nie miala zadnego przedzialu to dodajemy ten ktory aktualnie przetwarzamy
			else 
			{
				pair<int,int> current = mapa[wynik];
				if(a < current.first || (a == current.first && b < current.second)) //aktualizujemy tylko jesli a < || (a== && b <)
					mapa[wynik] = {a,b};		
			}
			a++, b++;
		}
	}
	for(int start = 22; start <= 42; start++)
	{
		a = 1, b = start;
		while(a <= 24) {
			long long wynik = przedzial(a,b);
			if(wynik == 0) //useless przedzial
			{
				a++, b++;
				continue;
			}
			if(mapa.count(wynik) == 0) mapa[wynik] = {a,b};//jesli liczba nie miala zadnego przedzialu to dodajemy ten ktory aktualnie przetwarzamy
			else 
			{
				pair<int,int> current = mapa[wynik];
				if(a < current.first || (a == current.first && b < current.second)) //aktualizujemy tylko jesli a < || (a== && b <)
					mapa[wynik] = {a,b};		
			}
			a++, b++;
		}
	}	
}

int main()
{
	ios_base::sync_with_stdio(0);
	init();
	int z;
	cin>>z;
	/*for(auto it = mapa.begin(); it != mapa.end(); it++)
	{
		cout<<it->first<<"= <"<<it->second.first<<","<<it->second.second<<"> 			licznik="<<licznik++<<"\n";
	}*/
	for(int i = 1; i <= z; i++) {
		long long a;
		cin>>a;
		ans(a);
	}
	return 0;
}
