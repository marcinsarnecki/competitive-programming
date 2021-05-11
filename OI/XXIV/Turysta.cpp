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

#define N 2001
int n;
int graf[N][N];

list<vector<int>> cykle;

void wczytaj() {
	cin>>n;
	int x;
	rep(i,2,n) {
		rep(j,1,i-1) {
			cin>>x;
			if(x == 1)
				graf[j][i] = 1;
			else
				graf[i][j] = 1;
		}
	}
}

bool corner1(int v) {//wszystkie aktualne wierzcholki do v
	for(auto &cykl: cykle) {
		for(auto u: cykl) {
			if(graf[u][v] == 0)
				return false;
		}
	}
	return true;
}

bool corner2(int v) {//z v do wszystkich aktualnych wierzcholkow
	for(auto &cykl: cykle) {
		for(auto u: cykl) {
			if(graf[v][u] == 0)
				return false;
		}
	}
	return true;
}

bool check1(vector<int> &cykl, int v) { //czy v posiada krawedz do cyklu
	for(auto u: cykl) 
		if(graf[v][u])
			return true;
	return false;
}

bool check2(vector<int> &cykl, int v) { //czy w cyklu jest krawedz do v
	for(auto u: cykl) 
		if(graf[u][v])
			return true;
	return false;
}

vector<int> wlozDoPoczatkowego(vector<int> &cykl, int v) {
	vector<int> nowyCykl{v};
	int lacznik = -1;
	for(auto u: cykl) {
		if(lacznik == -1 && graf[v][u]) 
			lacznik = u;
		if(lacznik != -1)
			nowyCykl.pb(u);
	}
	for(auto u: cykl) {
		if(u == lacznik)
			break;
		nowyCykl.pb(u);
	}
	return nowyCykl;
}

vector<int> wlozDoKoncowego(vector<int> &cykl, int v) {
	vector<int> nowyCykl;
	int lacznik = -1;
	for(auto u: cykl) {
		if(lacznik != -1)
			nowyCykl.pb(u);
		if(lacznik == -1 && graf[u][v]) 
			lacznik = u;
	}
	for(auto u: cykl) {
		nowyCykl.pb(u);
		if(u == lacznik)
			break;
	}
	return nowyCykl;
}

vector<int> wlozDoSrodkowego(vector<int> &cykl, int v) {
	int pos;
	for(int i = 0; i < cykl.size(); i++) {
		int u = cykl[i], w = (i == cykl.size()-1) ? cykl[0] : cykl[i+1];
		if(graf[u][v] && graf[v][w]) {
			pos = i;
			break;
		}
	}
	vector<int> nowyCykl;
	for(int i = 0; i <= pos; i++) {
		nowyCykl.pb(cykl[i]);
	}
	nowyCykl.pb(v);
	for(int i = pos + 1; i < cykl.size(); i++)
		nowyCykl.pb(cykl[i]);
	return nowyCykl;
}

void solve() {
	cykle.push_front(vector<int>{1});//poczatkowy vector z jednym wierzcholkiem '1'
	rep(v,2,n) {
		if(corner1(v)) {
			cykle.push_back(vector<int>{v});
			continue;
		}
		if(corner2(v)) {
			cykle.push_front(vector<int>{v});
			continue;
		}
		int l = 1, r = cykle.size();
		for(auto &cykl : cykle) {//pierwsza z lewej do cyklu
			if(check1(cykl, v)) 
				break;
			l++;
		}
		for(auto it = cykle.rbegin(); it != cykle.rend(); it++) {//pierwsza z prawej z cyklu do v
			if(check2(*it,v)) 
				break;
			r--;
		}
		if(l < r) {//nowy cykl!
			auto it = cykle.begin();
			advance(it, l-1);
			auto poczatkowy = it;
			vector<int> pierwszy = wlozDoPoczatkowego(*it,v);
			vector<int> srodek;
			for(int i = 1; i <= r - l - 1; i++) {
				++it;
				srodek.insert(srodek.end(), (*it).begin(), (*it).end());
			}
			++it;
			auto koncowy = it;
			vector<int> ostatni = wlozDoKoncowego(*it, v);//pierwszy i ostatni vector z nowego cyklu
			vector<int> nowyCykl;
			nowyCykl.insert(nowyCykl.end(),pierwszy.begin(),pierwszy.end());
			nowyCykl.insert(nowyCykl.end(),srodek.begin(),srodek.end());
			nowyCykl.insert(nowyCykl.end(),ostatni.begin(),ostatni.end());
			koncowy++;
			cykle.erase(poczatkowy,koncowy);
			it = cykle.begin();
			advance(it,l-1);
			if(cykle.size() == 0)
				cykle.push_back(nowyCykl);
			else
				cykle.insert(it, nowyCykl);
		}
		if(r < l) {
			vector<int> nowyCykl{v};
			auto it = cykle.begin();
			advance(it,l-1);
			cykle.insert(it,nowyCykl);
		}
		if(l == r) {
			auto it = cykle.begin();
			advance(it,l-1);
			vector<int> nowyCykl = wlozDoSrodkowego(*it,v);
			it = cykle.erase(it);
			if(cykle.size() == 0)
				cykle.push_back(nowyCykl);
			else
				cykle.insert(it, nowyCykl);
		}
		
	}
}

bool zawiera(vector<int> &cykl, int v) {
	for(auto u: cykl)
		if(u == v)
			return true;
	return false;
}

void wypiszSciezke(int v) {
	vector<int> ans;
	int pom = -1;
	int rest = 0;
	for(auto &cykl: cykle) {
		if(rest)
			for(auto u: cykl)
				ans.pb(u);
		else 
			if(zawiera(cykl,v)) {
				for(int i = 0; i < cykl.size(); i++) {
					if(cykl[i] == v)
						pom = i;
					if(pom != -1)
						ans.pb(cykl[i]);
				}
				for(int i = 0; i < pom; i++) 
					ans.pb(cykl[i]);
				rest = 1;
		}
	}
	cout<<ans.size()<<" ";
	for(auto u: ans)
		cout<<u<<" ";
	cout<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	solve();
	rep(i,1,n)
		wypiszSciezke(i);
	return 0;
}
