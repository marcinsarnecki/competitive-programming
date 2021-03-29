#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

#define INF 1000000
#define N 102

int tab[N][N];			// czy pole jest dostepne 
int odl[N][N][4];		// najmniejsza odleglosc do danego pola [][] gdy skonczylismy w nim idac w kierunku 0/1/2/3
int visited[N][N][4];	// czy odwiedzilismy dane pole [][] idac w kierunku 0/1/2/3
int dirnext[N][N][4];	// w ktora strone isc w nastepnym kroku podczas odtwarzania sciezki
int n, m, ans = INF;
pii A, B;

int dy[]{ -1,0,1,0 };	//tablice odpowiednich przesuniec w wierzu i kolumnie dla danego kierunku
int dx[]{ 0,1,0,-1 };	//0 gora / 1 prawo / 2 dol / 3 lewo
	
queue<pair<pii, int>> Q;// <i,j>, dir

void wej() {
	cin >> n >> m;
	rep(i, 1, n) {
		rep(j, 1, m) {
			char z;
			cin >> z;
			if (z == 49)
				tab[i][j] = 1;
		}
	}
	cin >> A.f >> A.s >> B.f >> B.s;
}

void init() {
	rep(i, 0, n) tab[i][0] = tab[i][m + 1] = 1; //otoczka dokola planszy zeby nie wyjsc poza nia
	rep(j, 0, m) tab[0][j] = tab[n + 1][j] = 1;
	rep(i, 1, n)
		rep(j, 1, m)
		odl[i][j][0] = odl[i][j][1] = odl[i][j][2] = odl[i][j][3] = INF;//poczatkowo odleglosc do kazdego wierzcholka jest rowna INF

}

void solve() {
	if (tab[A.f][A.s] == 1 || tab[B.f][B.s] == 1) {//brzegowy przypadek kiedy pole startowe/koncowe jest niedostepne
		cout << "NIE\n";
		return;
	}

	visited[A.f][A.s][0] = visited[A.f][A.s][1] = visited[A.f][A.s][2] = visited[A.f][A.s][3] = 1;	//poczatkowy wierzcholek odwiedzony 
	odl[A.f][A.s][0] = odl[A.f][A.s][1] = odl[A.f][A.s][2] = odl[A.f][A.s][3] = 1;					//z odlegloscia startowa rowna 1

	Q.push({ A,0 });//poczatek BFS'a
	Q.push({ A,1 });
	Q.push({ A,2 });
	Q.push({ A,3 });

	while (Q.size()) {
		pair<pii, int> temp = Q.front();
		Q.pop();

		int dir = temp.s, dir2 = (dir + 1) % 4;			//dir - w ktorym kierunku weszlismy do wierzcholka //dir2 - prawo z perspektywy dir
		pii v = temp.f;									//aktualny wierzcholek
		pii u1 = { v.f + dy[dir], v.s + dx[dir] };		//nastepny wierzcholek jesli idziemy prosto
		pii u2 = { v.f + dy[dir2], v.s + dx[dir2] };	//nastepny wierzcholek jesli skrecamy w prawo

		if (tab[u1.f][u1.s] == 0 && visited[u1.f][u1.s][dir] == 0) {//do przodu
			visited[u1.f][u1.s][dir] = 1;
			odl[u1.f][u1.s][dir] = odl[v.f][v.s][dir] + 1;
			dirnext[v.f][v.s][(dir + 2) % 4] = (dir + 2) % 4;//przy odtwarzaniu sciezki musi byc informacja dla przeciwnego kierunku w ktora strone isc dalej	
			Q.push({ u1,dir });
		}

		if (tab[u2.f][u2.s] == 0 && visited[u2.f][u2.s][dir2] == 0) {//w prawo
			visited[u2.f][u2.s][dir2] = 1;
			odl[u2.f][u2.s][dir2] = odl[v.f][v.s][dir] + 1;
			dirnext[v.f][v.s][(dir2 + 2) % 4] = (dir + 2) % 4;
			Q.push({ u2,dir2 });
		}
	}

	rep(i, 0, 3) 
		ans = min(ans, odl[B.f][B.s][i]);

	if (ans == INF)  
		cout<< "NIE\n";

	else {
		cout << ans << "\n";
		int dir;
		pii v = B; //aktualny wierzcholek przy odtwarzaniu sciezki
		list<pii> sciezka;
		if (ans == odl[B.f][B.s][0]) dir = 2;//ustalenie kierunku skad uzyskalismy odpowiedz
		if (ans == odl[B.f][B.s][1]) dir = 3;
		if (ans == odl[B.f][B.s][2]) dir = 0;
		if (ans == odl[B.f][B.s][3]) dir = 1;
		while (v != A) {
			sciezka.push_front(v);
			v.f += dy[dir];
			v.s += dx[dir];
			dir = dirnext[v.f][v.s][dir];//dirnext jest obliczane w trakcie bfsa, linijki 74 i 81
		}
		sciezka.push_front(A);
		for (auto it : sciezka)
			cout << it.f << " " << it.s << "\n";
	}
}

int main() {
	wej();
	init();
	solve();
}
