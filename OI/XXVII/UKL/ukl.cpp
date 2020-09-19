#include<bits/stdc++.h>
using namespace std;
int visited[1005][1005];//[wiersze][kolumny]
int n,m,k,z,idx;
pair<int,int> ans[1000001][2];

void buduj(int i, int j, int ile, int dir)// 0 gora 1 prawo 2 lewo 3 dol, ile kraw, buduje prosta sciezke o dlugosci ile w kierunku dir zaczynajac od i,j
{
	if(ile == 0) return;
	if(dir == 0)//gora
	{
		for(int l = 1; l <= ile; l++) 
		{
			visited[i][j] = 1;
			visited[i-1][j] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i-1,j};
			i--;
		}
	}
	if(dir == 1)//prawo
	{
		for(int l = 1; l <= ile; l++) 
		{
			visited[i][j] = 1;
			visited[i][j+1] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i,j + 1};
			j++;
		}
	}
	if(dir == 2)//dol
	{
		for(int l = 1; l <= ile; l++) 
		{
			visited[i][j] = 1;
			visited[i+1][j] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i+1,j};
			i++;
		}
	}
	if(dir == 3)//lewo
	{
		for(int l = 1; l <= ile; l++) 
		{
			visited[i][j] = 1;
			visited[i][j-1] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i,j-1};
			j--;
		}
	}
}

void odnoga(int i, int j, int dir)
{
	if(dir == 0)//gora
	{
		while(visited[i-1][j] == 0) {
			if(i == 1) return;
			visited[i-1][j] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i-1,j};
			i--;
		}
	}
	if(dir == 1)//prawo
	{
		while(visited[i][j+1] == 0) {
			if(j == m) return;
			visited[i][j+1] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i,j+1};
			j++;
		}
	}
	if(dir == 2)//dol
	{
		while(visited[i+1][j] == 0) {
			if(i == n) return;
			visited[i+1][j] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i+1,j};
			i++;
		}
	}
	if(dir == 3)//lewo
	{
		while(visited[i][j-1] == 0) {
			if(j == 1) return;
			visited[i][j-1] = 1;
			ans[idx][0] = {i,j};
			ans[idx++][1] = {i,j-1};
			j--;
		}
	}
}

void wypisz()
{
	cout<<"TAK\n";
	if(z == 0) for(int i = 0; i < idx; i++) cout<<ans[i][0].first<<" "<<ans[i][0].second<<" "<<ans[i][1].first<<" "<<ans[i][1].second<<"\n";
	if(z == 1) for(int i = 0; i < idx; i++) cout<<ans[i][0].second<<" "<<ans[i][0].first<<" "<<ans[i][1].second<<" "<<ans[i][1].first<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m>>k;
	if(n < m) {
		swap(n,m);
		z = 1;//zamiana wierszy kolumn
	}
	if(m == 1) {//corner case szerokosc = 1
		if(k == n - 1) 
		{
			buduj(1,1,n-1,2);
			wypisz();
			return 0;
		}
		else 
		{
			cout<<"NIE\n";
			return 0;	
		}
	}
	
	if(n == 2 && m == 2) {//corner case plansza 2x2
		if(k == 3) {
			cout<<"TAK\n";
			cout<<"1 1 1 2\n";
			cout<<"1 1 2 1\n";
			cout<<"1 2 2 2";
			return 0;
		}
		else
		{
			cout<<"NIE\n";
			return 0;
		}
	}
	
	if(m == 2) { //corner case plansza 2xn
		if(n % 2 == 1) {//ladny przypadek
			if(k > n * m - 1 || k < n) {
				cout<<"NIE\n";
				return 0;
			}
			buduj(1,1,n/2,2);
			buduj(n,2,n/2,0);
			buduj((n/2)+1,1,1,1);
			k -= n;
			if(k > 0) {
				buduj(1,1,1,1);
				k--;
				int d = min(k,(n/2)-1);
				buduj(1,2,d,2);
				k -= d;
			}	
			if(k > 0) {
				buduj(n,2,1,3);
				k--;
				int d = min(k,(n/2)-1);
				buduj(n,1,d,0);
				k -= d;
			}
			odnoga((n/2)+1,1,2);
			odnoga((n/2)+1,2,0);
			wypisz();
			return 0;	
		}
		else { // m=2 n%2==0
			if(k < n + 1 || k > n * m - 1) {
				cout<<"NIE\n";
				return 0;
			}
			buduj(1,1,1,1);
			buduj(n,1,1,1);
			buduj(1,2,n - 1,2);
			k -= n + 1;
			buduj(1,1,k,2);
			for(int i = 1; i <= n; i++) odnoga(i,2,3);
			wypisz();
			return 0;
		}
	}
	
	if(z) {
		swap(n,m);
		z = 0;
	}
	
	if(n % 2 == 0 && m % 2 == 0) {//parzyste wymiary :(
		if(k < n + m - 1 || k > (n*m) - 1) {
			cout<<"NIE\n";
			return 0;
		}
		if(k <= (n*m/2)+n-1) {//pierwszy zawijaniec
			buduj(1,m,m/2,3);
			buduj(n,m,m/2,3);
			buduj(1,m/2,n-1,2);
			k -= n + m - 1;
			buduj(n,m,min(k,n - 2),0);
			k -= min(k,n-2);
			int i = 2, j = m;
			while(k > 0)
			{
				if(i == 2) {
					buduj(i,j,1,3);
					k--;
					j--;
					buduj(i,j,min(k,n-3),2);
					k -= min(k,n-3);
					i = n - 1;
				}
				else {
					buduj(i,j,1,3);
					k--;
					j--;
					buduj(i,j,min(k,n-3),0);
					k -= min(k,n-3);
					i = 2;
				}
			}
			for(int i = 1; i <= n; i++) {
				odnoga(i,m/2,1);
				odnoga(i,m/2,3);
			}
			wypisz();
			return 0;
		}
		else {//drugi zawijaniec
			buduj(1,1,m-1,1);
			buduj(1,1,n-1,2);
			buduj(n,1,m-1,1);
			k -= m + m + n - 3;
			buduj(n,m,min(k,n-2),0);
			k -= min(k,n-2);
			int i = 2, j = m;
			while(k > 0)
			{
				if(i == 2) {
					buduj(i,j,1,3);
					k--;
					j--;
					buduj(i,j,min(k,n-3),2);
					k -= min(k,n-3);
					i = n - 1;
				}
				else {
					buduj(i,j,1,3);
					k--;
					j--;
					buduj(i,j,min(k,n-3),0);
					k -= min(k,n-3);
					i = 2;
				}
			}
			for(int i = 1; i <= n; i++) odnoga(i,1,1);
			wypisz();
			return 0;
		}
	}
	
	if(m%2 == 0) {//zeby m bylo nieparzyste
		swap(n,m);
		z = 1;
	}
	
	if(k < n + m - 2 || k > (n*m) - 1) {
		cout<<"NIE\n";
		return 0;
	}
	
	buduj(1,1,m/2,1);
	buduj(n,m,m/2,3);
	buduj(1,(m/2)+1,n-1,2);
	k -= n + m - 2;
	buduj(n,m,min(k,n-1),0);
	k -= min(k,n-1);
	int i = 1, j = m;
	while(k > 0 && j > (m/2)+2)
	{
		if(i == 1) {
			buduj(i,j,1,3);
			k--;
			j--;
			buduj(i,j,min(k,n-2),2);
			k -= min(k,n-2);
			i = n - 1;
		}
		else {
			buduj(i,j,1,3);
			k--;
			j--;
			buduj(i,j,min(k,n-2),0);
			k -= min(k,n-2);
			i = 1;
		}
	}
	buduj(1,1,min(k,n-1),2);
	k -= min(k,n-1);
	i = n, j = 1;
	while(k > 0)
	{
		if(i == n) {
			buduj(i,j,1,1);
			k--;
			j++;
			buduj(i,j,min(k,n-2),0);
			k -= min(k,n-2);
			i = 2;
		}
		else
		{
			buduj(i,j,1,1);
			k--;
			j++;
			buduj(i,j,min(k,n-2),2);
			k -= min(k,n-2);
			i = n;
		}
	}
	for(int i = 1; i <= n; i++) {
		odnoga(i,(m/2)+1,1);
		odnoga(i,(m/2)+1,3);
	}
	wypisz();
	return 0;
}
