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

#define N 10001

int n, z[N], d[N], v1, v2;
ll d1, d2; //odleglosci do aktualnych koncow wierzcholka (d1 to odleglosc do v1 zgodnie z ruchem wskazowek zegara, d2 do v2 przeciwnie)
ll ile1, ile2;//ile jest wierzcholkow w jednej trasie i drugiej
ll Ans = INF, current;//koncowy i aktualny wynik

void popraw() { //szukamy optymalnych 2 koncow 
	while(d1 + d[v1] < d2) {//jesli dystans do pierwszego konca + krawedz nastepna < dystans do drugiego to wtedy sie oplaca przesunac konce 
		current = current + z[v2] * (d1 + d[v1]) - z[v2] * d2;
		ile1 += z[v2];
		ile2 -= z[v2];
		d1 += d[v1];
		d2 -= d[v2];
		v1 = (v1 == n) ? 1 : v1 + 1;
		v2 = (v2 == n) ? 1 : v2 + 1;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n)
		cin>>z[i]>>d[i];
	repv(i,n,2) {//wstepnie ustawiamy sytuacje w ktorej v1 = 1 oraz v2 = 2
		d2 += d[i];
		ile2 += z[i];
		current += d2 * z[i];
	}
	v1 = 1, v2 = 2;
	popraw();
	Ans = current; //odpowiedz dla browaru w miejscu 1
	rep(i,2,n) {//pozniej liczymy optymalny wynik dla browaru w kazdym kolejnym wierzcholku
		int kraw = d[i-1];
		current = current - (ile1 * kraw) + ((ile2 + z[i-1]) * kraw);
		ile1 -= z[i];
		ile2 += z[i-1];
		d1 -= kraw;
		d2 += kraw;
		popraw();
		Ans = min(Ans, current);
	}
	cout<<Ans;
	return 0;
}
