#include<bits/stdc++.h>
#define N 100001
using namespace std;

vector<int> graf[N], GT[N];
int InDegree[N], czas[N];
long long najdluzsza, MaxDo[N], MaxPo[N];//MaxDo to najciezsza sciezka do wierzcholka wlacznie z nim, MaxPo analogicznie
int n, q, m[N], d[N];


queue<int> Q;
vector<int> order;



int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++)
	{
		int a,b;
		cin>>czas[i]>>a;
		for(int j = 1; j <= a; j++)
		{
			cin>>b;
			graf[b].push_back(i);
			GT[i].push_back(b);
			InDegree[i]++;
		}
	}
	cin>>q;
	for(int i = 1; i <= q; i++)
		cin>>m[i]>>d[i];
		
	
	for(int i = 1; i <= n; i++) //dodanie poczatkowych wierzcholkow 
	{
		if(InDegree[i] == 0) Q.push(i);
	}
	
	while(!Q.empty()) //sortowanie topologiczne
	{
		int v = Q.front();
		Q.pop();
		order.push_back(v);
		for(int i = 0; i < graf[v].size(); i++)
		{
			InDegree[graf[v][i]]--;
			if(InDegree[graf[v][i]] == 0) Q.push(graf[v][i]);
		}
	}
	
	if(order.size() != n) //jesli nie wszystkie wierzcholki zostaly przetworzone to znaczy ze mamy cykl
	{
		cout<<"CYKL";
		return 0;
	}
	
	for(int i = 0; i < order.size(); i++)//maksymalne sciezki do wierzcholka i zaczynajace sie w nim wlacznie z nim
	{
		int v = order[i];
		for(int j = 0; j < GT[v].size(); j++)
			MaxDo[v] = max(MaxDo[v], MaxDo[GT[v][j]]);
		MaxDo[v] += czas[v];
	}
	for(int i = order.size() - 1; i >= 0; i--)
	{
		int v = order[i];
		for(int j = 0; j < graf[v].size(); j++)
			MaxPo[v] = max(MaxPo[v], MaxPo[graf[v][j]]);
		MaxPo[v] += czas[v];
	}
	
	for(int i = 1; i <= n; i++) najdluzsza = max(najdluzsza, MaxDo[i] + MaxPo[i] - czas[i]);//najdluzsza sciezka, izi pizi
	cout<<najdluzsza<<"\n";
	
	for(int i = 1; i <= q; i++)
	{
		if(MaxDo[m[i]] + MaxPo[m[i]] - czas[m[i]] + d[i] > najdluzsza) cout<<"TAK\n";//izi pizi
		else cout<<"NIE\n";
	}
	
	return 0;
}
