#include<bits/stdc++.h>
#define N 300001
using namespace std;
int tab[N], krazki[N];
int n,m;
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= n; i++) cin>>tab[i];
	for(int i = 1; i <= m; i++) cin>>krazki[i];
	for(int i = 2; i <= n; i++) tab[i] = min(tab[i], tab[i - 1]);//ciag nierosnacy
	int depth = n, idx = 1;
	while(idx <= m && depth >= 1){
		if(tab[depth] >= krazki[idx]){
			depth--;
			idx++;
		}
		else depth--;
	}
	if(idx > m) cout<<depth + 1;
	else cout<<"0";
	return 0;
}
