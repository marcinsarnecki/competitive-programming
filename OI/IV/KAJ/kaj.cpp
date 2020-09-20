#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int w,n,ans;
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>w>>n;
	v.resize(n);
	for(int i = 0; i < n; i++) cin>>v[i];
	sort(v.begin(),v.end());
	int i = 0, j = n - 1;//najlzejsze z lewej, najciezsze z prawej
	while(i <= j)//najlzejszy musi i tak plynac wiec dobieramy najciezszego z ktorym on moze plynac, a jak ten najciezszy nie pasuje to on i tak musi sam wiec samo j--, a tak to i++ j--
	{
		if(i == j) {
			ans++;
			i++;
		}
		else if(v[i] + v[j] <= w) {
			ans++;
			i++;
			j--;
		}
		else {
			ans++;
			j--;
		}
	}
	cout<<ans;
	return 0;
}
