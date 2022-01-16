#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int n,X,x,a,b,maxg,mind,d;

int main() {
	ios_base::sync_with_stdio(0);
	
	cin>>n>>X;
	for(int i=0;i<n;i++)
	{
		cin>>x>>a>>b;
		a++;
		b--;
		maxg+=x-d;
		mind-=x-d;
		d=x;
		if(maxg<a or mind>b)
		{
			cout<<"NIE";
			return 0;
		}
		if(mind<a)
		{
			if(abs(mind%2)==abs(a%2)) mind=a;
			else mind=a+1;
		}
		if(maxg>b)
		{
			if(abs(maxg%2)==abs(b%2)) maxg=b;
			else maxg=b-1;
		}
		if(mind>maxg)
		{
			cout<<"NIE";
			return 0;
		}	
	}
	cout<<(mind+x)/2;
	
	return 0;
}
