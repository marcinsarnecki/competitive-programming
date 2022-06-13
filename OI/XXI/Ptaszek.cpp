#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1000005

int tab[N], dp[N], n, q;
list<int> l1, l2;

void dodaj(int i) {
	while(l1.size() && tab[i] >= tab[l1.back()]) 
        l1.pop_back();
	l1.push_back(i);
}

void usun(int i) {
	if(l1.size() && l1.front() == i) l1.pop_front();
}

int best() {
	if(l1.size())
        return l1.front();
	return -1;
}

void popraw() {
	if(l1.size() > 0) 
        return;
	for(auto it: l2)
        dodaj(it);
	l2.clear();
}

void solve(int k) {
	if(k == 1) {
		rep(i,2,n) 
            if(tab[i] < tab[i - 1])
                dp[i] = dp[i - 1];
		else 
            dp[i] = dp[i - 1] + 1;
		cout<<dp[n]<<"\n";
		return;
	}
	l1.clear(), l2.clear();
	dp[1] = 0;
	l1.push_back(1);
	rep(i,2,n) {
		popraw();
		int idx = best();
		if(tab[i] < tab[idx]) {
			dp[i] = dp[idx];
			dodaj(i);
		}
		else  {
			dp[i] = dp[idx] + 1;
			l2.push_back(i);
		}
		if(i >= k + 1) {
			usun(i - k);
			if(l2.size() > 0 && l2.front() == i - k)
                l2.pop_front();
		}
	}
	cout<<dp[n]<<"\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n)
        cin>>tab[i];
	cin>>q;
	rep(i,1,q) {
		int k;
		cin>>k;
		solve(k);
	}
	return 0;
}
