#include<bits/stdc++.h>
#define N 201

using namespace std;

const long long INF = 1e18;
typedef vector<vector<long long>> vvll;
int n, m;
long long ans = INF;
string s[N];

struct matrix {
	vvll graf;
	void operator=(const matrix &b) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				graf[i][j] = b.graf[i][j];
	}
	void operator*=(const matrix &b) {
		vvll pom(n + 1);
		for(int i = 1; i <= n; i++) pom[i].resize(n + 1, INF); 
		for(int v = 1; v <= n; v++)
			for(int u = 1; u <= n; u++) {
				long long d = INF;
				for(int mid = 1; mid <= n; mid++) d = min(d, graf[v][mid] + b.graf[mid][u]);
				pom[v][u] = d;
			}
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				graf[i][j] = pom[i][j];
	}
	void ustaw() {
		graf.resize(n + 1);
		for(int i = 1; i <= n; i++) graf[i].resize(n + 1, INF);
	}
}graf, pom;

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

long long extend(string &A, string &B) {
	if(A == B) {
		vector<int> pi = kmp(A);
		return A.size() - pi.back();
	}
	string s = B + '#' + A;
	vector<int> pi = kmp(s);
	return B.size() - pi.back();
}

void make_graph(matrix &graf) {
	for(int v = 1; v <= n; v++) 
		for(int u = 1; u <= n; u++) 
			graf.graf[v][u] = extend(s[v], s[u]);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;//m - ile chomikow, m >= 1
	m--;//teraz ile krawedzi
	for(int i = 1; i <= n; i++) cin>>s[i];
	graf.ustaw();
	make_graph(graf);
	pom.ustaw();
	pom=graf;
	m--;//jeszcze raz bo startujemy juz z grafem 
	if(m == -1) {//corner case tylko 1 chomik jest odpowiedzia
		for(int i = 1; i <= n; i++) ans = min(ans, (long long)s[i].size());
		cout<<ans;
		return 0;
	}
	for(int i = 0; i < 31; i++) {
		if((1<<i) & m) 
			graf*=pom;
		pom*=pom;
	}
	for(int v = 1; v <= n; v++) 
		for(int u = 1; u <= n; u++)
			ans = min(ans, graf.graf[v][u] + ((long long)s[v].size()));
	cout<<ans;
	return 0;
}
