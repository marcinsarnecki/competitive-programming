#include<bits/stdc++.h>

using namespace std;

#define N 1000001
#define INF 1000010
vector<int> wystapienia[N];
int tab[N];
int z[N];

int m,n,l,granica,odp;

int nastepny(int value,int g) //funckja zwraca pierwsza pozycje value wieksza niz g
{
	if(wystapienia[value].size()==0) return INF;
	int lewo = 0,prawo = wystapienia[value].size()-1;
	int mid = (lewo+prawo)/2;
	while(!(wystapienia[value][mid]<=g && wystapienia[value][mid+1] > g))
	{
		if(wystapienia[value][mid]<g) lewo = mid+1;
		else prawo = mid;
		mid = (lewo + prawo)/2;
	}
	return wystapienia[value][mid+1];
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	cin>>m;
	for(int i = 1; i <= m; i++) 
	{
		cin>>tab[i];
		if(wystapienia[tab[i]].size()==0) wystapienia[tab[i]].push_back(-1);
		wystapienia[tab[i]].push_back(i);
	}
	for(int i = 1; i <= m; i++) wystapienia[tab[i]].push_back(INF);
	
	
	cin>>n;
	for(int j = 1; j <= n; j++)
	{
		cin>>l;
		granica = 0;
		odp = 1;
		for(int i = 1; i <= l; i++)
		{
			cin>>z[i];
		}
		for(int i = 1; i <= l; i++)
		{
			granica = nastepny(z[i],granica);
			if(granica==INF) 
			{
				odp = 0;
			}
			if(odp == 0) break;
		}
		if(odp) cout<<"TAK\n";
		else cout<<"NIE\n";
		
		
	}
	
	
	
	
	
	return 0;
}
