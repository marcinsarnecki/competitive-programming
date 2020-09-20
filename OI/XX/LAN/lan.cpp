#include<bits/stdc++.h>
#define N 1000001
using namespace std;
int l[N],licznik[N];//ile powinno byc itego koloru (nie jest rowne l[] z tresci zadania, tutaj juz jest uzgodniony indeks z kolorem), licznik ile czego jest na biezaco
int n,m,ile;//ile dobrych kolorow jest w aktualnie rozwazanym lancuchu
int wej1[N], wej2[N], lancuch[N], wynik;
long long len;//WAZNE dlugosc lancucha w long long poniewaz mozemy miec n roznych lancuchow z wymaganiem kazdy ilosc n, odp oczywiscie na nie ale int moze sie przekrecic
void dodaj(int kolor)
{
	if(l[kolor] == 0) return;
	licznik[kolor]++;
	if(licznik[kolor] == l[kolor]) ile++;
	if(licznik[kolor] == l[kolor] + 1) ile--;
}
void usun(int kolor)
{
	if(l[kolor] == 0) return;
	licznik[kolor]--;
	if(licznik[kolor] == l[kolor]) ile++;
	if(licznik[kolor] == l[kolor] - 1) ile--;
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++) {
		cin>>wej1[i];
		len += wej1[i];
	}
	for(int i = 1; i <= m; i++) cin>>wej2[i];
	for(int i = 1; i <= n; i++) cin>>lancuch[i];
	
	if(len > n)	{
		cout<<"0";
		return 0;
	}
	
	for(int i = 1; i <= n; i++) l[wej2[i]] = wej1[i];//l[] ile powinno byc itego koloru
	
	for(int i = 1; i <= len; i++) if(l[lancuch[i]] > 0) dodaj(lancuch[i]);
	if(ile == m) wynik++;
	
	for(int i = len + 1; i <= n; i++)
	{
		dodaj(lancuch[i]);
		usun(lancuch[i - len]);
		if(ile == m) wynik++;
	}	
	cout<<wynik;
	return 0;
}
