#include<bits/stdc++.h>
using namespace std;
#define NTREE 1048576
#define N 1000001
struct litera
{
	char z;
	int pos;
	litera(char a,int b)
	{
		z = a;
		pos = b;
	}
};
list<litera> l;
char wzorzec[N];
vector<int> pozycje[26];
vector<list<litera>::iterator> iteratory[26];
int last[26];//patrzymy na last a potem go zwiekszamy pozycje[last[nasza litera]]
int tree[2 * NTREE], n;
long long wynik;
void dodaj(int value,int l,int r)
{
	l += NTREE;
	r += NTREE;
	if(l == r)
	{
		tree[l] += value;
		return;
	}
	tree[l] += value;
	tree[r] += value;
	while(r - l > 1)
	{
		if(l % 2 == 0) tree[l + 1] += value;
		if(r % 2 == 1) tree[r - 1] += value;
		l /= 2;
		r /= 2;
	}
}
int query(int pos)
{
	pos += NTREE;
	int sum = 0;
	while(pos)
	{
		sum += tree[pos];
		pos /= 2;
	}
	return sum;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++)
	{
		char z;
		cin>>z;
		l.push_back(litera(z,i));
		pozycje[z - 65].push_back(i);
		iteratory[z - 65].push_back(--l.end());
	}
	for(int i = 1; i <= n; i++)
	{
		char z;
		cin>>z;
		wzorzec[i] = z;
	}
	list<litera>::iterator it = l.begin();
	int i = 1, pos = 1;
	while(it != l.end())
	{
		char a = (*it).z;
		int p = (*it).z;
		char szukana = wzorzec[i];
		if(a == szukana)//litery pasuja
		{
			pos++;
			i++;
			it++;
			last[a - 65]++;
		}
		else//nie pasuja
		{
			int k = last[szukana - 65]++;
			list<litera>::iterator it2 = iteratory[szukana - 65][k];
			int pos2 = pozycje[szukana - 65][k];//it2 to wskaznik na szukana w liscie, pos2 to jej pozycja
			dodaj(1, 1, pos2 - 1);
			pos2 += query(pos2);//zaktualizowana pozycja pos2
			wynik += (pos2 - pos);
			l.erase(it2);
			pos++;
			i++;
			
		}
		
	}
	
	cout<<wynik;
	return 0;
}
