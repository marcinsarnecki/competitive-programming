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

int n, k;
int a[N], kolizje;
vector<int> pos[N], output;//numery pozycji na wejsciu dla danego rozmiaru
priority_queue<pii> Q;

void wczytaj() {
	cin>>n>>k;
	rep(i,1,n) {
		cin>>a[i];
		a[i] = (a[i] + 1) % k;//uproszczenie
		pos[a[i]].pb(i);
	}
}

void solve() { //pary <ilosc,dlugosc>
	for(auto it: pos[0]) output.pb(it);//mozna od razu wypisac wszystkie wiersze, ktora sa wielokrotnosciami s
	rep(i,1,k-1)
		if(pos[i].size())
			Q.push({pos[i].size(), i});
	int current = 0;
	while(Q.size()) {
		pii p1 = Q.top();
		Q.pop();
		int ile1 = p1.f, d1 = p1.s;
		if(Q.size() == 0) { //nic innego nie da sie zrobic
			for(auto it: pos[d1]) {
				if(current == k-1) {
					kolizje++;
					current = 0;//
				}
				current = (current + d1) % k;
				output.pb(it);
			}
			break;
		}
		if(current + d1 == k-1) {//trzeba wypisac drugi najczestszy
			pii p2 = Q.top();
			Q.pop();
			int ile2 = p2.f, d2 = p2.s;

			current = (current + d2) % k;
			output.pb(pos[d2].back());
			pos[d2].pop_back();
			ile2--;
			if(ile2 > 0) Q.push({ile2,d2});
			Q.push({ile1,d1});
		}
		else {//nie trzeba, nie ma kolizji
			current = (current + d1) % k;
			output.pb(pos[d1].back());
			pos[d1].pop_back();
			ile1--;
			if(ile1 > 0) Q.push({ile1,d1});
		}
	}
	cout<<kolizje<<"\n";
	for(auto it: output)
		cout<<it<<" ";
}

int main() {
	wczytaj();
	solve();
	return 0;
}
