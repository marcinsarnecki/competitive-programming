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

vector<int> kmp(string &s) {
	int n = s.size();
	vector<int> pi(n);
	for(int i = 1; i < n; i++) {
		int j = pi[i-1];
		while(j > 0 && s[i] != s[j])
			j = pi[j-1];
		if(s[i] == s[j])
			j++;
		pi[i] = j;
	}
	return pi;
}

int main() {
	ios_base::sync_with_stdio(0);
	string napis;
	cin>>napis;
	vector<int> pi = kmp(napis);
	rep(i,0,pi.size()-1) cout<<"pi["<<i<<"] = "<<pi[i]<<"\n";
	return 0;
}
