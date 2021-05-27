#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const long long INF = 1000000000000000000ll;

#define N 500001

int n, all, d[N], ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n) {
		cin>>d[i];
		all += d[i];
	}
	int j = 1, current = 0;
	rep(i,1,n) {
		while(current < all/2) {
			current += d[j];
			ans = max(ans, min(current, all - current));
			j = (j == n) ? 1 : j + 1;
		}
		current -= d[i];
		ans = max(ans, min(current, all - current));
	}
	cout<<ans;
	return 0;
}
