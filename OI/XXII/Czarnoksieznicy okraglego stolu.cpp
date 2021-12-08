#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000001
#define mod 1000000007
int n, k, p, x[N], y[N];
bool blocked[N][7];

void add(int a, int b) {
	if(abs(a-b) <= p)
		blocked[a][b-a+3] = 1;
}

bool enemy(int a, int b) {//czy a nie lubi b
	if(abs(a-b) > p) //jesli > p to mozemy uznac ze sie nie lubia
		return true;
	return blocked[a][b-a+3];
}

int skaluj(int a) {
	return n-a;
}


bool check(vector<int> &v, bool t) {//czy podanay ciag czarnoksieznikow jest ok
	for(int i = 0; i < (int)v.size() - 1; i++)
		if(enemy(v[i], v[i+1]))
			return false;
	if(t && enemy(v.back(), v[0]))
		return false;
	return true;
}

void corner_case0() {//jesli p == 0 to tylko n moze byc rowne 1, inaczej nic sie nie da zrobic
	if(n == 1)
		cout<<"1\n";
	else
		cout<<"0\n";
}

void corner_case1() {//p == 1, albo n == 1 albo dwie osoby ktore sie lubia
	if(n == 1 || (n == 2 && !enemy(0,1) && !enemy(1,0))) 
		cout<<"1\n";
	else
		cout<<"0\n";
}

void corner_case2() {//p == 2
	if(n == 1) {
		cout<<"1\n";
		return;
	}
	int ans = 0;
	vector<int> v;
	v.pb(0);//jedyna mozliwoscia jest ulozenie 0 2 4 ... n-4 n-2 n-1 n-3 n-5 n-7 n-9(dla n parzystego)
	int idx = 2;//dla nieparzystego 0 2 4 ... m-5 n-3 n-1 n-2 n-4 n-6 n-8 ...
	while(idx <= n-1) {
		v.pb(idx);
		idx += 2;
	}
	n % 2 == 0 ? idx = n-1: idx = n-2;
	while(idx >= 1) {
		v.pb(idx);
		idx -= 2;
	}
	if(check(v, 1))
		ans++;
	reverse(v.begin(), v.end());
	if(check(v, 1))
		ans++;
	cout<<ans<<"\n";
}

void brut() {
	if(n == 1) {
		cout<<"1\n";
		return;
	}
	vector<int> v;
	rep(i,0,n-1)
		v.pb(i);
	int ans = 0;
	do{
		if(check(v, 1))
			ans++;
	}while(next_permutation(v.begin()+1, v.end()));//PERMUTACJE OD DRUGIEJ POZYCJI !!! 0 sie nie rusza
	cout<<ans<<"\n";
}

void solve() {
	for(int i = n-2; i >= n-8; i--) { //brut x[i] y[i] poczatkowe wartosci (od konca)
		vector<int> v;
		v.pb(i);
		for(int j = i + 2; j <= n-1; j++)
			v.pb(j);
		v.pb(i+1);
		do{
			if(check(v, 0))
				x[i]++;
			reverse(v.begin(), v.end());
			if(check(v, 0))
				y[i]++;
			reverse(v.begin(), v.end());	
		}while(next_permutation(v.begin() + 1, v.end() - 1));
	}
	for(int i = n-9; i >= 0; i--) {// liczenie x[i] y[i] ogolnym wzorem
		vector<int> v1, v2;
		
		v1 = {i, i+2}; // check 02...1 wiec sprawdzamy konflikt 0-2
		if(check(v1, 0)) 
			x[i] = (x[i] + y[i+1]) % mod;
		reverse(v1.begin(), v1.end());
		if(check(v1,0))
			y[i] = (y[i] + x[i+1]) % mod;
		
		v1 = {i, i+3}; // check 03...21 sprawdzamy konflikty 0-3 i 2-1 (kolejnosc jest wazna!)
		v2 = {i+2, i+1};
		if(check(v1, 0) && check(v2, 0))
			x[i] = (x[i] + y[i+2]) % mod;
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		if(check(v1, 0) && check(v2, 0))
			y[i] = (y[i] + x[i+2]) % mod;
		
		v1 = {i, i+3, i+2, i+5}; // check 0325...41
		v2 = {i+4, i+1};
		if(check(v1, 0) && check(v2, 0))
			x[i] = (x[i] + y[i+4]) % mod;
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		if(check(v1, 0) && check(v2, 0))
			y[i] = (y[i] + x[i+4]) % mod;
		
		v1 = {i, i+3, i+6}; // check 036...5241
		v2 = {i+5, i+2, i+4, i+1};
		if(check(v1, 0) && check(v2, 0))
			x[i] = (x[i] + y[i+5]) % mod;
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		if(check(v1, 0) && check(v2, 0))
			y[i] = (y[i] + x[i+5]) % mod;
	}
	int ans = 0;
	vector<int> v1, v2; 
	
	v1 = {1, 0};
	if(check(v1, 0)) // 0...1
		ans = (ans + x[0]) % mod;
	
	v1 = {0, 1};
	v2 = {2, 0};
	if(check(v1, 0) && check(v2, 0)) // 01...2
		ans = (ans + x[1]) % mod;
		
	v1 = {0, 3};
	v2 = {4, 1, 2, 0};
	if(check(v1, 0) && check(v2, 0)) // 03...412
		ans = (ans + x[3]) % mod;
	
	v1 = {0, 3, 1, 4};
	v2 = {5, 2, 0};
	if(check(v1, 0) && check(v2, 0)) // 0314...52
		ans = (ans + x[4]) % mod;
	
	v1 = {0, 1, 2};
	v2 = {3, 0};
	if(check(v1, 0) && check(v2, 0)) // 012...3
		ans = (ans + x[2]) % mod;
	
	v1 = {0, 1, 4};
	v2 = {5, 2, 3, 0};
	if(check(v1, 0) && check(v2, 0)) // 014...523
		ans = (ans + x[4]) % mod;
		
	v1 = {0, 1, 4, 2, 5};
	v2 = {6, 3, 0};
	if(check(v1, 0) && check(v2, 0)) // 01425...63
		ans = (ans + x[5]) % mod;
	
	v1 = {0, 2, 1, 4};
	v2 = {3, 0};
	if(check(v1, 0) && check(v2, 0)) // 0214...3
		ans = (ans + y[3]) % mod;
	
	v1 = {0, 2, 5};
	v2 = {4, 1, 3, 0};
	if(check(v1, 0) && check(v2, 0)) // 025...413
		ans = (ans + y[4]) % mod;
		
	cout<<ans<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>k>>p;
	rep(i,1,k) {
		int a, b;
		cin>>a>>b;
		add(skaluj(a), skaluj(b));
	}
	if(p == 0)
		corner_case0();
	if(p == 1)
		corner_case1();
	if(p == 2)
		corner_case2();
	if(p == 3) {
		if(n <= 8)
			brut();
		else
			solve();
	}
	return 0;
}
