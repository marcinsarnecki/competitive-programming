#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 3001
int l[N][26], n, idx;
string s[N];
vector<int> v[N];

bool check(int a, int b) {//czy dwa slowa o indeksach a b sa anagramami
	rep(i,0,25)
		if(l[a][i] != l[b][i])
			return false;
	return true;
}

bool cmp1(int a, int b) {//porownanie alfabetyczne slow o indeksach a b
	return s[a] < s[b];
}

bool cmp2(int a, int b) {//porownanie alfabetyczne dwoch klas anagramow (ich pierwszych slow)
	return s[v[a][0]] < s[v[b][0]];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n) {
		cin>>s[i];
			for(char c: s[i])
				l[i][c-97]++;
	}
	rep(i,1,n) {
		bool b = 0;
		rep(j,1,idx)
			if(check(i, v[j][0])) {
				v[j].pb(i);
				b = 1;
				break;
			}
		if(!b)
			v[++idx].pb(i);
	}
	rep(i,1,idx)
		sort(v[i].begin(), v[i].end(), cmp1);
	vector<int> order;//kolejnosc klas abstrakcji
	rep(i,1,idx)
		order.pb(i);
	sort(order.begin(), order.end(), cmp2);
	for(int i: order) {
		unordered_set<string> all;
		for(int j: v[i]) 
			if(all.find(s[j]) == all.end()) {
				cout<<s[j]<<" ";
				all.insert(s[j]);
			}
		cout<<"\n";
	}
	
	return 0;
}
