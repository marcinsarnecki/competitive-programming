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

bool graf[N][N];
bool erased[N];//czy wierzcholek zostal usuniety
int n, m;

void wczytaj() {
	cin>>n>>m;
	rep(i,1,m) {
		int a, b;
		cin>>a>>b;
		graf[a][b] = 1;
		graf[b][a] = 1;
	}
}

void solve() {
	for(int i = 1; i <= n; i++) 
		for(int j = i + 1; j <= n && !erased[i]; j++) 
			if(!graf[i][j] && !erased[j]) {//jesli 'i' i 'j' sie nie znaja oraz nie zostaly juz wczesniej usuniete
				erased[i] = 1;
				erased[j] = 1;
			}
	int left = n/3;
	for(int i = 1; i <= n && left > 0; i++) 
		if(!erased[i]) {
			left--;
			cout<<i<<" ";
		}
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	return 0;
}
