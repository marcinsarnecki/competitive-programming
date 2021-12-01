#include<bits/stdc++.h>
#include "cgdzlib.h"
#define fi first
#define se second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

pii dfs(vector<int> &ind, int level) {//zwraca pare indeksow min max, level to liczba dzielaca roznice liczb pod danymi indeksami
	if(ind.size() == 1) //koniec rekurencji
		return {ind[0], -1};
	if(ind.size() == 2) //koniec rekurencji
		return {ind[0], ind[1]};
	int d = level * 2, dif = (ind.size() - 1) * level;//dif to roznica pomiedzy min max z aktualnych liczb z indeksow (ind)
	vector<int> ind1, ind2;//indeksy w lewym i prawym poddrzewie
	ind1.pb(ind[0]);
	for(int i = 1; i < (int)ind.size(); i++) 
		if(f(ind[0], ind[i], d))
			ind1.pb(ind[i]);
		else
			ind2.pb(ind[i]);
	pii p1 = dfs(ind1, d); //pary indeksow min max
	pii p2 = dfs(ind2, d); //jesli przedzial dlugosci 1 to wtedy para indeks, -1
	if(p1.se != -1 && f(p1.fi, p1.se, dif)) //wszystkie mozliwosci (jest ich 6) ze sprawdzeniem czy nie probujemy uzyc -1
		return {p1.fi, p1.se};
	if(p2.se != -1 && f(p2.fi, p2.se, dif))
		return {p2.fi, p2.se};
	if(f(p1.fi, p2.fi, dif))
		return {p1.fi, p2.fi};
	if(p2.se != -1 &&f(p1.fi, p2.se, dif))
		return {p1.fi, p2.se};
	if(p1.se != -1 && f(p1.se, p2.fi, dif))
		return {p1.se, p2.fi};
	if(p1.se != -1 && p2.se != -1 && f(p1.se, p2.se, dif))
		return {p1.se, p2.se};
}

int main() {
	ios_base::sync_with_stdio(0);
	srand(time(NULL));
	int n = inicjuj();
	if(n == 1) {
		odpowiedz(1);
		return 0;
	}
	vector<int> b;
	rep(i,1,n)
		b.pb(i);
	pii minmax = dfs(b, 1);//otrzymujac pare indeksow min max wystarczy raz uzyc g()
	g(minmax.fi, minmax.se) ? odpowiedz(minmax.se) : odpowiedz(minmax.fi);
	return 0;
}
