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

#define N 1000001
ll p = 31, mod = 1e9+7;
ll pN[N], hashe[N];

int n;
string s;

void init() {
	pN[0] = 1;
	rep(i,1,n)
		pN[i] = (pN[i-1] * p) % mod;
	repv(i,n,1)
		hashe[i] = (s[i-1] * pN[1] + hashe[i+1] * pN[1]) % mod;
}

ll gethash(int pos, int len) {
	ll ans = (hashe[pos] - hashe[pos+len] * pN[len]) % mod;
	if(ans < 0) ans += mod;
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>s;
	n = s.size();
	init();
	//od teraz gethash(pos,len) zwroci prawidlowy hash fragmentu dlugosci len na pozycji pos
	return 0;
}
