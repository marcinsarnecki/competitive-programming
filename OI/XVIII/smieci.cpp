#include<bits/stdc++.h>
#define N 100001
using namespace std;

list<pair<int,int> > graf[N];//pary sasiad-nr kraw
int n,m;

vector<int> cykle[1000005];
int ileCykli, visited[N];
vector<int> eulerCycle;

stack<int> stos;
int OnStack[N];

int nr;
struct krawedz
{
	int a,b;
	list<pair<int,int> >::iterator it1,it2;
}kraw[1000005];

void odetnij(int numer)//odcinanie kraw w O(1)
{
	graf[kraw[numer].a].erase(kraw[numer].it1);
	graf[kraw[numer].b].erase(kraw[numer].it2);
}

void dfsEuler(int v)
{
	while(graf[v].size())
	{
		list<pair<int,int> >::iterator it = graf[v].begin();
		int u = (*it).first, numer = (*it).second;
		odetnij(numer);
		dfsEuler(u);
	}
	eulerCycle.push_back(v);
}

void findEulerCycle(int start)//znajduje cykl eulera startujac z wierzcholka start i zapisuje go od razu ladnie
{
	eulerCycle.clear();//czyszczenie
	while(stos.size()) stos.pop();//czyszczenie
	dfsEuler(start);
	for(int i = 0; i < eulerCycle.size(); i++) //rozlozenie cyklu eulera na cykle proste z uzyciem pomocniczego stacku
	{
		int v = eulerCycle[i];
		if(OnStack[v]){
			cykle[ileCykli].push_back(v);
			while(stos.top() != v)
			{
				OnStack[stos.top()] = 0;
				cykle[ileCykli].push_back(stos.top());
				stos.pop();
			}
			cykle[ileCykli++].push_back(v);
		}
		else{
			OnStack[v] = 1;
			stos.push(v);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		if(c!=d)
		{
			graf[a].push_front(make_pair(b,nr));
			graf[b].push_front(make_pair(a,nr));
			kraw[nr].a = a;
			kraw[nr].b = b;
			kraw[nr].it1 = graf[a].begin();
			kraw[nr++].it2 = graf[b].begin();
		}
	}
	
	for(int i = 1; i <= n; i++) if(graf[i].size() % 2 == 1) {
		cout<<"NIE";
		return 0;
	}
	
	for(int i = 1; i <= n; i++) if(graf[i].size()) findEulerCycle(i);
	
	cout<<ileCykli<<"\n";
	for(int i = 0; i < ileCykli; i++){
		cout<<cykle[i].size() - 1<<" ";
		for(int j = 0; j < cykle[i].size(); j++) cout<<cykle[i][j]<<" ";
		cout<<"\n";
	}
	
	return 0;
}
