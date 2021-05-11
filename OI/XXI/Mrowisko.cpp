#include<bits/stdc++.h>
using namespace std;
vector<int> graf[1000005];
int n, g, k, wa, wb, s1, s2;//dwa wierzcholki startowe
vector<int> grupy;
long long wynik;

long long dodaj(int a, int b)//dodanie do wyniku, przedzial <a,b> w lisciu i sprawdzenie ile liczb w grupy jest z tego przedzialu razy k
{
	return (long long)(upper_bound(grupy.begin(),grupy.end(),b) - lower_bound(grupy.begin(),grupy.end(),a)) * k;
}

void dfs(int v,int parent, int a, int b) // <a,b) ile ma wejsc do tego v zeby bylo ok :)
{
	if(graf[v].size() == 1) //lisc
	{
		wynik += dodaj(a, b - 1);
		return;
	}
	int d = graf[v].size() - 1;
	for(int i = 0; i < graf[v].size(); i++) 
	{
		if(graf[v][i] != parent)
		{
			dfs(graf[v][i], v, min((long long)a * d, (long long)1e9+1), min((long long)b * d, (long long)1e9+1));
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>g>>k;
	grupy.push_back(-1);
	grupy.push_back(1000000005);//wartownicy
	for(int i = 1; i <= g; i++) {
		cin>>wa;
		grupy.push_back(wa);
	}
	for(int i = 1; i < n; i++) {
		cin>>wa>>wb;
		if(i == 1) {
			s1 = wa;
			s2 = wb;
		}
		graf[wa].push_back(wb);
		graf[wb].push_back(wa);
	}
	sort(grupy.begin(), grupy.end());
	dfs(s1,s2,k,k + 1);
	dfs(s2,s1,k,k + 1);
	cout<<wynik;
	return 0;
}
