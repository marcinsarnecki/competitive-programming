#include<bits/stdc++.h>

using namespace std;

vector<int> v;
int a;

int main()
{
	ios_base::sync_with_stdio(0);
	while(1) {
		cin>>a;
		if(a == 0) break; 
		else v.push_back(a);
	}
	sort(v.begin(),v.end());
	for(int i = 0; i < v.size()-2; i++) {
		if(v[i]+v[i+1]>v[i+2]) {
			cout<<v[i]<<" "<<v[i+1]<<" "<<v[i+2]<<"\n";
			return 0;
		}
	}
	cout<<"NIE\n";
	return 0;
}
