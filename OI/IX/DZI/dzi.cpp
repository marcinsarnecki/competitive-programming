#include<bits/stdc++.h>
#define N 2005
using namespace std;
int depth[N][N]; 
bool tab[N][N];
int n;
int L[N], R[N];//indeksy na lewo i prawo pierwszego mniejszego (czyli pierwsze miejsce gdzie juz nie pasuje), z tym mozemy obliczyc max prostakat (rozwaz przyklad 3 8 8 5 8 8 3 :) )

int wiersz(int i)//maksymalnny prostokat majacy bok w tym wierszu
{
	stack<pair<int,int>> s;//wysokosc,indeks
	
	s.push({-1,0});//wartownik, w prawo
	for(int j = 1; j <= n; j++)
	{
		while(s.top().first >= depth[i][j]) s.pop();
		L[j] = s.top().second;
		s.push({depth[i][j],j});//wysokosc, indeks
	}
	
	while(s.size()) s.pop();
	
	s.push({-1,n + 1});
	for(int j = n; j >= 1; j--)
	{
		while(s.top().first >= depth[i][j]) s.pop();
		R[j] = s.top().second;
		s.push({depth[i][j],j});
	}
	
	int ans = 0;
	for(int j = 1; j <= n; j++) ans = max(ans, (R[j] - L[j] - 1) * depth[i][j]);
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin>>tab[i][j];
	
	for(int j = 1; j <= n; j++){
		for(int i = n; i >= 1; i--){
			if(tab[i][j] == 1) depth[i][j] = 0;
			else depth[i][j] = depth[i + 1][j] + 1;
		}
	}	
	int wynik = 0;
	for(int i = 1; i <= n; i++) wynik = max(wynik, wiersz(i));
	cout<<wynik;
	return 0;
}
