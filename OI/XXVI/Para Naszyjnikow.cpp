#include<bits/stdc++.h>
#define N 100005
using namespace std;
int q,n,m,ans,last1,last0,k1,k2,parmax1,parmax2,a1,a2;
int left0[N][2], right0[N][2], left1[N][2], right1[N][2], pref1[N][2], tab2[N], tab1[N];
int main()
{
	ios_base::sync_with_stdio(0);//
	cin>>q;
	for(int test = 1; test <= q; test++)
	{
		ans = k1 = k2 = 0;
		cin>>n>>m;
		if(n < m)
		{
			for(int i = 1; i <= n; i++){
				cin>>tab2[i];
				tab2[i] = tab2[i] % 2;
			}
			for(int i = 1; i <= m; i++){
				cin>>tab1[i];
				tab1[i] = tab1[i] % 2;
			}
			swap(n,m);
		}
		else
		{
			for(int i = 1; i <= n; i++){
				cin>>tab1[i];
				tab1[i] = tab1[i] % 2;
			}
			for(int i = 1; i <= m; i++){
				cin>>tab2[i];
				tab2[i] = tab2[i] % 2;
			}
		}
		last1 = last0 = 0;
		for(int i = 1; i <= n; i++){//wstepny preprocessing
			if(tab1[i] == 0) last0 = i;
			if(tab1[i] == 1) last1 = i;
			left1[i][0] = last1;
			left0[i][0] = last0;
		}	
		last1 = last0 = N;
		for(int i = n; i >= 1; i--){//wstepny preprocessing
			if(tab1[i] == 0) last0 = i;
			if(tab1[i] == 1) last1 = i;
			right1[i][0] = last1;
			right0[i][0] = last0;
		}
		last1 = last0 = 0;
		for(int i = 1; i <= m; i++){//wstepny preprocessing
			if(tab2[i] == 0) last0 = i;
			if(tab2[i] == 1) last1 = i;
			left1[i][1] = last1;
			left0[i][1] = last0;
		}
		last1 = last0 = N;
		for(int i = m; i >= 1; i--){//wstepny preprocessing
			if(tab2[i] == 0) last0 = i;
			if(tab2[i] == 1) last1 = i;
			right1[i][1] = last1;
			right0[i][1] = last0;
		}
		for(int i = 1; i <= n; i++){//wstepny preprocessing
			pref1[i][0] = pref1[i - 1][0];
			if(tab1[i] == 1) pref1[i][0]++;
		}
		for(int i = 1; i <= m; i++){//wstepny preprocessing
			pref1[i][1] = pref1[i - 1][1];
			if(tab2[i] == 1) pref1[i][1]++;
		}
		parmax1 = pref1[m][1] % 2;
		parmax2 = pref1[m - 1][1] % 2;
		if(right1[1][1] != N && left0[m][1] != 0){//pierwsze 0 ostatnia 1 
			k2 = max(k2, left0[m][1] - right1[1][1]);
		}
		if(right0[1][1] != N && left1[m][1] != 0){//pierwsza 1 ostatnie 0
			k2 = max(k2, left1[m][1] - right0[1][1]);
		}
		ans = max(ans, k2);
		for(int i = 1; i <= n - m + 1; i++)
		{
			k1 = 0;
			if(right0[i][0] <= i + m - 1 && left1[i + m - 1][0] >= i){
				k1 = max(k1, left1[i + m - 1][0] - right0[i][0]);
			}
			if(right1[i][0] <= i + m - 1 && left0[i + m - 1][0] >= i){
				k1 = max(k1, left0[i + m - 1][0] - right1[i][0]);
			}
			ans = max(ans, k1);
			a1 = (pref1[i + m - 1][0] - pref1[i - 1][0]) % 2;
			if(m > 1) a2 = (pref1[i + m - 2][0] - pref1[i - 1][0]) % 2;
			if(a1 == parmax1) ans = max(ans, m);
			if(m > 1 && a2 == parmax2) ans = max(ans, m - 1);
		}
		cout<<ans<<"\n";
	}
	
	return 0;
}
