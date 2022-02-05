#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 92
ll fib[N+1];

int solve(ll k) {
	if(k == 1 || k == 2 || k == 3)
		return 1;
	rep(i,4,N-1) {
		if(k == fib[i] || k == fib[i+1])
			return 1;
		if(fib[i] < k && k < fib[i+1]) {
			ll dif1 = k - fib[i], dif2 = fib[i+1] - k;
			return (dif1 < dif2) ? 1 + solve(dif1) : 1 + solve(dif2);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	fib[1] = fib[2] = 1;
	rep(i,2,N)
		fib[i] = fib[i-1] + fib[i-2];
	int t;
	cin>>t;
	while(t--) {
		ll k;
		cin>>k;
		cout<<solve(k)<<"\n";
	}
	return 0;
}
