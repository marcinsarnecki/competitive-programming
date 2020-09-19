#include<bits/stdc++.h>

using namespace std;

#define ntree 4098
#define N 100001

int tree[2*ntree];
map<int,int> mapa[N];
int tab[3001][3001];
int n,m,k,maksi;
long long sumall;

void insert(int l,int p,int value)//dodanie od l do p wartosci value
{
	l+=ntree;
	p+=ntree;
	if(l>p) return;
	if(l==p) 
	{
		tree[l]+=value;
		return;
	}
	tree[l]+=value;
	tree[p]+=value;
	while(p-l>1)
	{
		if(l%2==0) tree[l+1]+=value;
		if(p%2==1) tree[p-1]+=value;
		l/=2;
		p/=2;
	}
}

int query(int p)
{
	p+=ntree;
	int sum=0;
	while(p>1)
	{
		sum+=tree[p];
		p/=2;
	}
	return sum;
}


void addkolumna(int j)
{
		for(int i = 1; i <= n; i++)
		{
			int v = tab[i][j];
			map<int,int>::iterator vi = mapa[v].find(i);
			if(vi!=mapa[v].end()&&vi->second!=0)//mapa[v][i] != 0
			{
				vi->second++;
			}
			else
			{
				mapa[v][i]=1;
				vi=mapa[v].find(i);
				map<int,int>::iterator itgora=vi;
				itgora++;
				map<int,int>::iterator itdol=vi;
				itdol--;
				
				int y2 = itgora->first;
				int y1 = itdol->first;
				//y2 to gora a y1 dol poprawnie wyliczone 
				int l = i-k+1;
				int p = i; //lewo i prawo potencjalnego przedzialu
				if(l<y1+1) l=y1+1;
				if(p>y2-k) p=y2-k;
				//zaktualizowane 
				insert(l,p,1);
			}
		}
}

void rmvkolumna(int j)
{
	for(int i = 1; i <= n; i++)
	{
		  int v = tab[i][j];
			map<int,int>::iterator vi = mapa[v].find(i);
			if(vi!=mapa[v].end()&&vi->second!=1)//mapa[v][i]!=1
			{
				vi->second--;
			}
			else
			{
				map<int,int>::iterator itgora=vi;
				map<int,int>::iterator itdol=vi;
				itgora++;
				itdol--;
				mapa[v].erase(vi);
				
				int y2 = itgora->first;
				int y1 = itdol->first;
				int l = i-k+1;
				int p = i;
				if(l<y1+1) l=y1+1;
				if(p>y2-k) p=y2-k;
				//zaktualizowane 
				insert(l,p,-1);
			}
	}
}

void addwynik()
{
	for(int i = 1; i <= n-k+1; i++)
	{
		int x = query(i);
		maksi=max(maksi,x);
		sumall+=x;
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m>>k;
	for(int i = n; i >= 1; i--)
		for(int j = 1; j <= m; j++)
			cin>>tab[i][j];
	
	for(int i = 1; i < N; i++)
	{
		mapa[i][0]=1;
		mapa[i][N+k]=1;
	}
	
	for(int j = 1; j<= k; j++)
		addkolumna(j);
	
	addwynik();
	
	for(int j = k + 1; j <= m; j++)
	{
		rmvkolumna(j-k);
		addkolumna(j);
		addwynik();
	}
	cout<<maksi<<" "<<sumall;
	return 0;
}
