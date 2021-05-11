#include<bits/stdc++.h> //patrzac do tylu (zasieg k) wartosci dp roznia sie co najwyzej o 1, trzymamy 2 zbiory A i B (mniejszych i o 1 wiekszych), zawsze patrzymy na najwieksze drzewo
#define N 1000005//z A, jesli zbior A sie wyczerpie to przenosimy wszystkie z B do A i kontynuujemy, kolejka kmax
using namespace std;

int tab[N], dp[N], n, q;
list<int> l1, l2;

void dodajA(int i)
{
	while(l1.size() && tab[i] >= tab[l1.back()]) l1.pop_back();
	l1.push_back(i);
}

void usunA(int i)
{
	if(l1.size() && l1.front() == i) l1.pop_front();
}

int bestA()
{
	if(l1.size()) return l1.front();
	return -1;//empty A
}

void dodajB(int i)
{
	while(l2.size() && tab[i] >= tab[l2.back()]) l2.pop_back();
	l2.push_back(i);
}

void usunB(int i)
{
	if(l2.size() && l2.front() == i) l2.pop_front();
}

int bestB()
{
	if(l2.size()) return l2.front();
	return -1;//empty B
}

void popraw()
{
	if(l1.size()) return;
	for(auto it: l2) l1.push_back(it);
	l2.clear();
}

void solve(int k)
{
	if(k == 1) {//corner case
		for(int i = 2; i <= n; i++) if(tab[i] < tab[i - 1]) dp[i] = dp[i - 1];
		else dp[i] = dp[i - 1] + 1;
		cout<<dp[n]<<"\n";
		return;
	}
	l1.clear();
	l2.clear();
	dp[1] = 0;
	l1.push_back(1);
	for(int i = 2; i <= n; i++)
	{
		popraw();
		int best = bestA();
		if(tab[i] < tab[best]) 
		{
			dp[i] = dp[best];
			dodajA(i);
		}
		else 
		{
			dp[i] = dp[best] + 1;
			dodajB(i);
		}
		if(i >= k + 1) {
			usunA(i - k);
			usunB(i - k);
		}
	}
	cout<<dp[n]<<"\n";
	return;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>tab[i];
	cin>>q;
	for(int i = 1; i <= q; i++) {
		int w1;
		cin>>w1;
		solve(w1);
	}
	return 0;
}
