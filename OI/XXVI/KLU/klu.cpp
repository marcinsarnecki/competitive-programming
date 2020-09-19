#include<bits/stdc++.h>
using namespace std;
int pref1[30][2000005], pref0[30][2000005], zle[30];
int n, m, wa;
int tab1[2000005], tab2[2000005], tab3[2000005];
long long ans;
bool przedzial(int a, int b)// <a,b>
{
	if(a == b)
	{
		for(int j = 0; j < n; j++) if(zle[j] == 0) return 0;
	}
	if(b < a)
	{
		for(int j = 0; j < n; j++)
		{
			if(zle[j] == 0)//brak zlego fragmentu
			{
				if(pref0[j][m] - pref0[j][a - 1] + pref0[j][b] == 0) return 0;
				if(pref1[j][m] - pref1[j][a - 1] + pref1[j][b] == 0) return 0;
			}
		}
		return 1;
	}
	for(int j = 0; j < n; j++)
	{
		if(zle[j] == 0)//brak zlego fragmentu
		{
			if(pref0[j][b] - pref0[j][a - 1] == 0) return 0;
			if(pref1[j][b] - pref1[j][a - 1] == 0) return 0;
		}
	}
	return 1;
}
int dystans(int a, int b)
{
	if(a <= b) return b - a + 1;
	return b + m - a + 1;
}
void count_tab1()
{
	int p = 1, k = 2;
	for(; p <= m; p++)
	{
		while(przedzial(p,k) == 0)//gasienica
		{
			k++;
			if(k > m) k = 1;
		}
		tab1[p] = k;
	}
}
void count_tab2()
{
	for(int i = 1; i <= m; i++)
	{
		if(tab2[tab1[i]] == 0) 
		{
			tab2[tab1[i]] = i;
			tab3[tab1[i]] = dystans(i, tab1[i]);//
		}
		else
		{
			if(dystans(i, tab1[i]) < tab3[tab1[i]]) tab2[tab1[i]] = i;//tutaj tez
		}
	}
}
void count_tab3()
{
	int first = 1;
	while(tab2[first] == 0) first++;//first
	
	for(int i = first + 1; i <= m; i++)// <first + 1, m>
	{
		if(tab2[i - 1] != 0) tab3[i] = tab2[i - 1];
		else tab3[i] = tab3[i - 1];	
	}
	
	if(tab2[m] != 0) tab3[1] = tab2[m];// <1>
	else tab3[1] = tab3[m];
	
	for(int i = 2; i <= first; i++) // <2, first>
	{
		if(tab2[i - 1] != 0) tab3[i] = tab2[i - 1];
		else tab3[i] = tab3[i - 1];	
	}
}
int count_ans(int i, int koniec, int lewo)
{
	if(i < koniec)
	{
		if(lewo >= i && lewo <= koniec) return 0;
		return dystans(koniec, lewo) - 1;
	}
	else
	{
		if(lewo > koniec && lewo < i) return dystans(koniec, lewo) - 1;
		return 0;
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= m; i++)
	{
		cin>>wa;
		for(int j = 0; j < n; j++)
		{
			if(wa % 2 == 1)
			{
				pref1[j][i] = pref1[j][i - 1] + 1;
				pref0[j][i] = pref0[j][i - 1];
			}
			else
			{
				pref1[j][i] = pref1[j][i - 1];
				pref0[j][i] = pref0[j][i - 1] + 1;
			}
			wa /= 2;
		}
	}
	for(int j = 0; j < n; j++) if(pref1[j][m] == m || pref0[j][m] == m) zle[j] = 1;
	
	count_tab1();
	count_tab2();
	count_tab3();
	
	for(int i = 1; i <= m; i++)	ans += count_ans(i, tab1[i], tab3[i]);
	
	cout<<ans / 2;
	
	return 0;
}
