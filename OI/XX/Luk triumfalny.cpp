#include<bits/stdc++.h>
#define N 300005
using namespace std;
int n,wa,wb,l,p,mid;
vector<int> graf[N];

int dp(int v,int p,int k)
{
	int sum = 0;
	for(auto u: graf[v])
	{
		if(u != p) sum += dp(u,v,k) + 1;
	}
	return max(0,sum - k);//bez maxa z 0 bylyby wartosci ujemne a one zle by wplywaly na wynik, wartosc ujemna przekazana z dolu na gore chyba pozwolilaby na pozytywna odp dla zbyt malego k
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i < n; i++)
	{
		cin>>wa>>wb;
		graf[wa].push_back(wb);
		graf[wb].push_back(wa);
	}
	l = 0, p = n;
	mid = (l + p) / 2;
	while(l <= p) {
		if(dp(1,1,mid) == 0) p = mid - 1;
		else l = mid + 1;
		mid = (l + p) / 2;
	}
	cout<<p + 1;
	return 0;
}
