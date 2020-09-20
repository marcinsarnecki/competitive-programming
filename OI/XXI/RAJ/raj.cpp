#include<bits/stdc++.h>
using namespace std;
int n,m,wa,wb,idx, NTREE = 524288;
int tree[2 * 524288];
vector<int> graf[500005];
pair<int,int> kraw[1000005];
list<int> lista;
int visited[500005];
int order[500005];//porzadek topologiczny
int gdzie[500005];//gdzie jest v w topo
int MaxEnding[500005], MaxStarting[500005];//najdluzsza sciezka konczaca sie i zaczynajaca w v
int MaxPrzed[500005], MaxPo[500005];//maksima prefiksowe i sufiksowe
int ansValue, ansV, current;

void dfs(int v)
{
	visited[v] = 1;
	for(int i = 0; i < graf[v].size(); i++)
	{
		if(visited[graf[v][i]] == 0) dfs(graf[v][i]);
	}
	lista.push_front(v);
}

void sortowanieTopologiczne()
{
	for(int i = 1; i <= n; i++) if(!visited[i]) dfs(i);
	
	for(list<int>::iterator it = lista.begin(); it != lista.end(); it++) 
	{
		order[++idx] = *it;
		gdzie[*it] = idx;
	}
}

void obliczMaxEnding()//najdluzsza sciezka konczaca sie w wierzcholku
{
	for(int i = 1; i <= idx; i++)
	{
		int v = order[i];
		for(int j = 0; j < graf[v].size(); j++)
		{
			int u = graf[v][j];
			MaxEnding[u] = max(MaxEnding[u], MaxEnding[v] + 1);
		}
	}
}

void obliczMaxStarting()//najdluzsza sciezka zaczynajaca sie z wierzcholka
{
	for(int i = idx; i >= 0; i--)
	{
		int v = order[i];
		for(int j = 0; j < graf[v].size(); j++)
		{
			int u = graf[v][j];
			MaxStarting[v] = max(MaxStarting[v], MaxStarting[u] + 1);
		}
	}
}

void obliczMaxPrzed()//maksima prefiksowe
{
	for(int i = 1; i <= idx; i++)
	{
		int v = order[i];
		MaxPrzed[i] = max(MaxPrzed[i - 1], MaxEnding[v]);
	}
}

void obliczMaxPo()//maksima sufiksowe
{
	for(int i = idx; i >= 1; i--)
	{
		int v = order[i];
		MaxPo[i] = max(MaxPo[i + 1], MaxStarting[v]);
	}
}

void update(int l, int r, int value) //maksowanie przedzialu wartoscia value
{
	if(l > r) return;
	l += NTREE;
	r += NTREE;
	tree[l] = max(tree[l], value);
	tree[r] = max(tree[r], value);
	while(r - l > 1)
	{
		if(l % 2 == 0) tree[l + 1] = max(tree[l + 1], value);
		if(r % 2 == 1) tree[r - 1] = max(tree[r - 1], value);
		l /= 2;
		r /= 2;
	}
}

int query(int pos)//maksimum w punkcie
{
	int ans = 0;
	pos += NTREE;
	while(pos)
	{
		ans = max(ans, tree[pos]);
		pos /= 2;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++)
	{
		cin>>wa>>wb;
		graf[wa].push_back(wb);
		kraw[i] = {wa,wb};
	}
	
	sortowanieTopologiczne();
	obliczMaxEnding();
	obliczMaxStarting();
	obliczMaxPrzed();
	obliczMaxPo();
	for(int i = 1; i <= m; i++)
	{
		int v = kraw[i].first, u = kraw[i].second;
		int longestPath = MaxEnding[v] + 1 + MaxStarting[u];//najdluzsza sciezka zawierajaca te krawedz, teraz update wierzcholkow miedzy ta krawedzia :)
		update(gdzie[v] + 1, gdzie[u] - 1, longestPath);
	}
	
	ansValue = 2000000, ansV = n + 1;//
	for(int i = 1; i <= n; i++)//dla kazdego v obliczanie najdluzszej sciezki bez v
	{
		current = max(MaxPrzed[gdzie[i] - 1], MaxPo[gdzie[i] + 1]);//sciezki konczace sie przed v i zaczynajace po v
		current = max(current, query(gdzie[i]));//sciezka ktorej krawedz omija v
		if(current < ansValue)
		{
			ansV = i;
			ansValue = current;
		}
	}
	cout<<ansV<<" "<<ansValue;
	
	return 0;
}
