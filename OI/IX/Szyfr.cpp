#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int n, S, a[40];

void input() {
	cin>>n;
	for(int i = 0; i < n; i++)	
		cin>>a[i];
	cin>>S;
}

void solve() {
	if(n <= 20) {//brut 
		for(int mask = 0; mask < (1<<n); mask++) {
			int sum = 0;
			for(int j = 0; j < n; j++) 
				if(mask & (1<<j))
					sum += a[j];
			if(sum == S) {
				for(int j = 0; j < n; j++) 
					if(mask & (1<<j))
						cout<<"1";
					else
						cout<<"0";
				return;
			}
		}
	}
	else {	//meet in the middle
		unordered_map<int,int> m;// sum -> mask
		vector<int> v1, v2;	//dwa zbiory liczb
		for(int i = 0; i < n; i++)	
			i < n/2 ? v1.pb(a[i]) : v2.pb(a[i]);
		for(int mask = 0; mask < (1<<v2.size()); mask++) { //mapowanie wszystkich sum z drugiego zbioru
			int sum = 0;
			for(int j = 0; j < (int)v2.size(); j++)
				if(mask & (1<<j))
					sum += v2[j];
			m[sum] = mask;
		}
		for(int mask = 0; mask < (1<<v1.size()); mask++) { 	//dla kazdej sumy w pierwszym zbiorze
			int sum = 0;									//sprawzdamy czy istnieje dopelnienie do S
			for(int j = 0; j < (int)v1.size(); j++)			//w drugim zbiorze
				if(mask & (1<<j))
					sum += v1[j];
			if(m.count(S - sum) > 0) {//wypisanie
				for(int j = 0; j < (int)v1.size(); j++) 
					if(mask & (1<<j))
						cout<<"1";
					else
						cout<<"0";
				mask = m[S - sum];
				for(int j = 0; j < (int)v2.size(); j++) 
					if(mask & (1<<j))
						cout<<"1";
					else
						cout<<"0";
				return;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	solve();
	return 0;
}
