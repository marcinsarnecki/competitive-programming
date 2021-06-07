#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define INF 1000000000
#define N 40001
vector<int> graf[N], odl1(N,INF), odl2(N,INF);
int n, m, visited[N], warstwy[5], r, ans;

queue<int> Q;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,m) {
		int a, b;
		cin>>a>>b;
		graf[a].pb(b);
		graf[b].pb(a);
	}
	odl1[1] = 0;
	visited[1] = 1;
	Q.push(1);
	while(Q.size()) {
		int v = Q.front();
		Q.pop();
		if(odl1[v] > 2)
			continue;
		for(auto u: graf[v]) {
			if(!visited[u]) {
				visited[u] = 1;
				odl1[u] = odl1[v] + 1;
				Q.push(u);
			}
		}
	}
	rep(i,1,n)
		visited[i] = 0;
	odl2[2] = 0;
	visited[2] = 1;
	Q.push(2);
	while(Q.size()) {
		int v = Q.front();
		Q.pop();
		if(odl2[v] > 2)
			continue;
		for(auto u: graf[v]) {
			if(!visited[u]) {
				visited[u] = 1;
				odl2[u] = odl2[v] + 1;
				Q.push(u);
			}
		}
	}
	
	rep(i,1,n) {
		if(odl1[i] == 1) warstwy[1]++;
		if(odl1[i] == 2) warstwy[2]++;
		if(odl2[i] == 1) warstwy[4]++;
		if(odl2[i] == 2) warstwy[3]++;
	}
	r = n - 2 - warstwy[1] - warstwy[2] - warstwy[3] - warstwy[4];
	ans = n * (n-1) / 2; 								//wszystkie
	ans -= m;											//juz istniejace
	ans -= (warstwy[2] + warstwy[3] + warstwy[4] + 1);	//miedzy 1 a wszystkim wierzcholkami poza warstwa 1
	ans -= warstwy[1] * (warstwy[3] + warstwy[4] + 1);	//miedzy warstwa 1 a reszta za warstwa 2
	ans -= warstwy[2] * (warstwy[4] + 1);				//miedzy warstwa 2 a reszta za warstwa 3
	ans -= warstwy[3];									//miedzy warstwa 3 a wierzcholkiem koncowym
	ans -= 2*r;											//reszta wierzcholkow z wierzcholkami 1,2
	ans -= r * min(warstwy[1], warstwy[4]);				//reszte doczepiamy do wiekszej warstwy nr 1 albo 4, wiec odejmujemy krawedzie do mniejszej z nich
	cout<<ans; 
	return 0;
}
