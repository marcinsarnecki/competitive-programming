#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = 1000000000000000000ll;

#define N 1001
vector<pair<int,int>> graf[N];//sasiad,waga
vector<ll> odl(N,INF);
priority_queue<pair<ll,int>> Q;//kolejka priorytetowa postaci -odleglosc,wierzcholek (-odleglosc * (-1) zeby brac zawsze ten z najmniejsza odl, kolejka jest typu max
int n,m;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	rep(i,1,m){
		int a,b,c;
		cin>>a>>b>>c;
		graf[a].pb({b,c});
		graf[b].pb({a,c});
	}
	odl[1] = 0;
	Q.push({0,1});
	while(!Q.empty())
	{
		ll distance = Q.top().f * (-1);
		int v = Q.top().s;
		Q.pop();
		if(distance > odl[v]) continue;
		for(int i = 0; i < graf[v].size(); i++){
			int u = graf[v][i].f;
			ll krawedz = graf[v][i].s;
			if(odl[u] > odl[v] + krawedz){
				odl[u] = distance + krawedz;
				Q.push(make_pair(-odl[u],u));
			}
		}
	}
	rep(i,1,n) cout<<"dystans do "<<i<<" wynosi "<<odl[i]<<"\n";
	return 0;
}
