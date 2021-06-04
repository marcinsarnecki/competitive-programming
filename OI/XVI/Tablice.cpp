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

#define N 1001
int n, m, tests;
int input1[N][N], input2[N][N];	//tablice z wejscia
int tab1[N][N], tab2[N][N];		//pomocnicze tablice
pii wiersze1[N], wiersze2[N];	//pomocnicze tablice sluzace do
pii kolumny1[N], kolumny2[N];	//ustalenia kolejnosci przy sprawdzaniu

bool solve() {
	cin>>n>>m;
	rep(i,1,n)
		rep(j,1,m) {
			cin>>input1[i][j];
			tab1[i][j] = input1[i][j];
		}
	rep(i,1,n)
		rep(j,1,m) {
			cin>>input2[i][j];
			tab2[i][j] = input2[i][j];
		}
	rep(i,1,n) {								//obserwacja: kazda operacja nie zmieni zawartosci w wierszach, zatem mozemy
		sort(tab1[i] + 1, tab1[i] + 1 + m);		//ustalic ktore wiersze powinny zawierac te same liczby, wiec sortujemy wiersze 
		sort(tab2[i] + 1, tab2[i] + 1 + m);		//aby uzyskac najmniejszy element w kazdym wierszu
	}
	rep(i,1,n) {								//tworzymy pomocnicze tablice z najmniejszymi elementami w wierszach
		wiersze1[i] = {tab1[i][1], i};			//sortujemy, uzyskujemy informacje ktore wiersze powinny zawierac te same liczby
		wiersze2[i] = {tab2[i][1], i};
	}
	sort(wiersze1 + 1, wiersze1 + 1 + n);
	sort(wiersze2 + 1, wiersze2 + 1 + n);
	int w1 = wiersze1[1].s, w2 = wiersze2[1].s;
	rep(j,1,m) {								//potrzebujemy jeszcze informacji o kolejnosci pomiedzy kolumnami, wiec
		kolumny1[j] = {input1[w1][j],j};		//wybieramy dwa wiersze w tablicach ktore powinny zawierac te same liczby
		kolumny2[j] = {input2[w2][j],j};		//i sprawdzamy w jakiej kolejnosci powinnismy porownywac liczby
	}
	sort(kolumny1 + 1, kolumny1 + 1 + m);
	sort(kolumny2 + 1, kolumny2 + 1 + m);
	rep(i,1,n) {								//od teraz tablice wiersze i kolumny zawieraja informacje ktore wiersze/kolumny
		w1 = wiersze1[i].s, w2 = wiersze2[i].s;	//powinny byc zawierac te same liczby, wiec sprawdzamy kazda liczbe z wejscia
		rep(j,1,m) {
			int k1 = kolumny1[j].s, k2 = kolumny2[j].s;
			if(input1[w1][k1] != input2[w2][k2])
				return false;					//jesli cokolwiek sie nie zgadza to falsz
		}
	}
	return true;								//jesli nic zlego nie znalezlismy to prawda 
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>tests;
	while(tests--) {
		if(solve())
			cout<<"TAK\n";
		else
			cout<<"NIE\n";
	}
	return 0;
}
