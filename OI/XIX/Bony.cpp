#include<bits/stdc++.h>
using namespace std;

int bony[1000005], maksi;//czy w itej paczce jest bon tak/nie oraz info -1 jesli jest zjedzona ta paczka
int m,n;//ile lacznie jest bonow oraz dni
int dni[1000005];//po kolei ile ludzi przychodzi w jaki dzien
int odkad[1000005];
long long klient;
vector<long long> ans;

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>m;
	for(int i = 1; i <= m; i++) {
		int a;
		cin>>a;
		bony[a] = 1;
		maksi = max(maksi, a);
	}
	
	cin>>n;
	int a;
	
	for(int i = 1; i <= n; i++) {
		cin>>a;
		int idx = odkad[a] + a;
		int k = 1;
		while(k <= a && idx <= maksi)
		{
			if(bony[idx] == 1)
			{
				bony[idx] = -1;
				ans.push_back(klient + k);
				k++;
			}
			if(bony[idx] == 0)
			{
				bony[idx] = -1;
				k++;
			}
			if(k <= a) idx += a;//bo k++ moze wyjsc poza a juz w tym whilu i sie zepsuje wszystko
		}
		klient += a;
		odkad[a] = idx;
		
	}
	
	
	
	cout<<ans.size()<<"\n";
	for(int i = 0; i < ans.size(); i++) cout<<ans[i]<<"\n";
	
	
	
	return 0;
}
