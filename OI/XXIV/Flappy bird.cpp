#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int n,X,x,a,b,d,g,last;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>X;
	rep(i,1,n) {
		cin>>x>>a>>b;
		a++;
		b--;
		g += x-last;
		d -= x-last;
		last = x;
		if(g < a || d > b) {
			cout<<"NIE";
			return 0;
		}
		if(d < a) {
			if(abs(d%2) == abs(a%2))
				d=a;
			else 
				d=a+1;
		}
		if(g > b) {
			if(abs(g%2) == abs(b%2)) 
				g=b;
			else 
				g=b-1;
		}
		if(d > g) {
			cout<<"NIE";
			return 0;
		}	
	}
	cout<<(x + d)/2;
	return 0;
}
