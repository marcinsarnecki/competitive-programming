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

#define N 300001

int n, a[N][3], m[N], idx[3][3];
bool pom[3];//czy w kolumnie znajduja sie wgl jakiekolwiek wartosci > 0
ll sum[N], ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n)
		rep(j,0,2)
			cin>>a[i][j];
	rep(i,1,n) {
		rep(j,0,2)
			pom[j] |= (a[i][j] > 0);
		m[i] = max(a[i][0], max(a[i][1], a[i][2])); //max w wierszu
		sum[i] = (ll) a[i][0] + a[i][1] + a[i][2]; //suma w wierszu
	}
	vector<pii> col1, col2, col3;
	rep(i,1,n) {
		col1.pb({m[i] - a[i][0], i});//max - dana liczba jest dodatkowym kosztem ktory trzeba poniesc jesli
		col2.pb({m[i] - a[i][1], i});//w danym wierszu nie wybierzemy maxa jako liczby ktora zostawiamy
		col3.pb({m[i] - a[i][2], i});
	}
	make_heap(col1.begin(), col1.end(), greater<pii>());//szukamy 3 najlepszych miejsc w kazdym wierszu i potem
	make_heap(col2.begin(), col2.end(), greater<pii>());//mozna po prostu sprawdzic wszystkie mozliwosci 
	make_heap(col3.begin(), col3.end(), greater<pii>());
	rep(i,0,2) {
		idx[i][0] = col1[i].s;//macierz z optymalnymi indeksami 
		idx[i][1] = col2[i].s;
		idx[i][2] = col3[i].s;
	}
	rep(i,1,n)
		ans += sum[i] - m[i];//podstawowy koszt
	ll best = INF;
	rep(i,0,2)
		rep(j,0,2)
			rep(k,0,2) {
				int idx1 = idx[i][0], idx2 = idx[j][1], idx3 = idx[k][2];
				if(idx1 == idx2 || idx1 == idx3 || idx2 == idx3)
					continue;
				ll current = 0;
				if(pom[0]) current += m[idx1] - a[idx1][0];
				if(pom[1]) current += m[idx2] - a[idx2][1];
				if(pom[2]) current += m[idx3] - a[idx3][2];
				best = min(best, current);
			}
	cout<<ans + best;
	return 0;
}
