#include<bits/stdc++.h> // k * (suma dlugosci tras)
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int INF = 1000000001;


#define N 1000001
int W, H, n, m;
pii A, B, pulapki[N];
bool bad[N];//pulapki
vector<int> graf[N];

int startowy, koncowy;//poczatkowwe i koncowe komnaty

bool visited[N]; //do bfsa
int odl[N];
queue<int> Q;

struct prostokat{
	int x1, y1, x2, y2;
}pola[N];

struct point{
	int pos, t, id;//t oznacza rodzaj punktu: -1 pulapka, 1 start, 2 koniec, 3 4 A B  
};

unordered_map<int,vector<point>> pionowe, poziome;//linie potrzebne do wyznaczenia grafu
map<int, vector<point>> linie;//linie pionowe wszyskich punktow (pulapki, start, koniec)

void wczytaj() {
	cin>>W>>H>>n>>m;
	cin>>A.f>>A.s;
	cin>>B.f>>B.s;
	rep(i,1,n) {
		int a, b, c, d;
		cin>>a>>b>>c>>d;
		int x1 = min(a, c), y1 = min(b, d), x2 = max(a, c), y2 = max(b, d);
		pionowe[x1].pb({y1,1,i});//dodajemy tylko z lewej strony i z gory
		poziome[y2].pb({x1,1,i});//szukamy krawedzi pozniej tylko z prawej strony / z dolu
		pola[i] = {x1,y1,x2,y2};
	}
	rep(i,1,m) 
		cin>>pulapki[i].f>>pulapki[i].s;
}

bool compare(const point& a, const point& b) {
	if(a.pos == b.pos)
		return a.t > b.t;
	return a.pos < b.pos;
}

void zbudujGraf() {
	for(auto &it: pionowe) { //sortowanie kazej linii
		vector<point> &v = it.s;
		v.pb({INF,0,0});
		sort(v.begin(), v.end(), compare);
	}
	for(auto &it: poziome) { //sortowanie kazdej linii
		vector<point> &v = it.s;
		v.pb({INF,0,0});
		sort(v.begin(), v.end(), compare);
	}
	rep(i,1,n) {//z prawej
		int x2 = pola[i].x2, y1 = pola[i].y1, y2 = pola[i].y2, v = i;
		vector<point> &linia = pionowe[x2];
		if(x2 == W||linia.size() == 0)
			continue;
		point p{y1,1,i};
		int idx = (upper_bound(linia.begin(), linia.end(), p, compare) - linia.begin()) - 1;
		while(idx < (int)linia.size() && linia[idx].pos < y2) {//idziemy po posortowanych punktach na linii i dodajemy krawedzie
			int u = linia[idx].id;
			graf[v].pb(u);
			graf[u].pb(v);
			idx++;
		}
	}
	rep(i,1,n) {//z dolu
		int y1 = pola[i].y1, x1 = pola[i].x1, x2 = pola[i].x2, v = i;
		vector<point> &linia = poziome[y1];
		if(y1 == 0||linia.size() == 0)
			continue;
		point p{x1,1,i};
		int idx = (upper_bound(linia.begin(), linia.end(), p, compare) - linia.begin()) - 1;
		while(idx < (int)linia.size() && linia[idx].pos < x2) {
			int u = linia[idx].id;
			graf[v].pb(u);
			graf[u].pb(v);
			idx++;
		}
	}
	
}

void znajdzPunkty() {
	rep(i,1,n) {
		int x1 = pola[i].x1, y1 = pola[i].y1, y2 = pola[i].y2;
		linie[x1].pb({y1, 1, i});
		linie[x1].pb({y2, 2, i});
	}
	linie[A.f].pb({A.s,3,0});
	linie[B.f].pb({B.s,4,0});
	rep(i,1,m) 
		linie[pulapki[i].f].pb({pulapki[i].s, -1, 0});
	for(auto &it: linie) {
		vector<point> &v = it.s;
		sort(v.begin(), v.end(), compare);//sortujemy wszystkie linie
	}	
	set<point, decltype(compare)*> poczatki(compare), konce(compare);//set z wlasnym comparatorem
	poczatki.insert({INF,1,0});//bez tego nie dziala
	konce.insert({INF,2,0});
	auto pom = linie.begin();
	vector<point> &pomv = pom -> s;
	for(auto it: pomv) {
		if(it.t == 1)
			poczatki.insert(it);//pierwsza linia
		if(it.t == 2)
			konce.insert(it);
	}
	pom++;
	while(pom != linie.end()) {									//pomysl jest taki: przetwarzamy po kolei kazda pionowa linie na ktorej sa jakiekolwiek punkty
		vector<point> &punkty = pom -> s;						//poczatki i konce to sety, na ktorym trzymamy wierzcholku prostokatow ktore sie jeszcze nie skonczyly,
		for(int i = 0; i < (int)punkty.size(); i++) {			//wiec jesli napotkamy na jakies wydarzenie (pulapka, poczatek, koniec) to wystarczy upper bound zeby 
			if(punkty[i].t == 1) { //poczatek					//znalezc komnate w ktorej to sie dzieje; zmiany w aktualnych prostokatach nie sa przypadkowe: jesli
				int y1 = punkty[i].pos;							//napotkamy na poczatek, to szukamy pierwszego punktu konczacego ktory pokrywalby sie na jednej linii poziomej
				int j = i + 1;									//z jakims koncem dotychczasowo rozpoczetych prostokatow, wszystkie dotyczasowe usuwamy i dodajemy nowe
				while(konce.find(punkty[j]) == konce.end())	//szukamy konca ktory pokrywalby sie w koncem jakiegos rozpoczatego prostokata	
					j++;									//j sie na nim zatrzyma
				int y2 = punkty[j].pos;
				while(konce.size()) {
					auto it = konce.upper_bound({y1, 2, 0});//usuwamy dotychczasowe
					if((*it).pos <= y2) 
						konce.erase(it);
					else
						break;
				}
				while(poczatki.size()) {
					auto it = poczatki.lower_bound({y1, 2, 0});//usuwamy dotychczasowe
					if((*it).pos < y2) 
						poczatki.erase(it);
					else
						break;
				}
				for(int k = i; k <= j; k++) {//dodajemy nowe
					if(punkty[k].t == 1)
						poczatki.insert(punkty[k]);
					if(punkty[k].t == 2)
						konce.insert(punkty[k]);
				}
				i = j;
			}
			if(punkty[i].t == -1) { //a jesli jest jakies wydarzenie to dzieki setom znajdujemy od razu komnate
				auto it = konce.upper_bound({punkty[i].pos, 2, 0});
				int v = (*it).id;
				bad[v] = 1;
			}
			if(punkty[i].t == 3) {
				auto it = konce.upper_bound({punkty[i].pos, 2, 0});
				int v = (*it).id;
				startowy = v;
			}
			if(punkty[i].t == 4) {
				auto it = konce.upper_bound({punkty[i].pos, 2, 0});
				int v = (*it).id;
				koncowy = v;
			}
		}
		pom++;
	}	
}

void bfs() {
	Q.push(startowy); //zwykly bfs liczacy odleglosci, omija komnaty-pulapki
	visited[startowy] = 1;
	odl[startowy] = 1;
	while(Q.size()) {
		int v = Q.front();
		Q.pop();
		for(auto u: graf[v]) {
			if(visited[u] == 0 && !bad[u]) {
				visited[u] = 1;
				odl[u] = odl[v] + 1;
				Q.push(u);
			}
		}
	}
	cout<<odl[koncowy];
}

int main() {
	ios_base::sync_with_stdio(0);
	wczytaj();
	zbudujGraf();
	znajdzPunkty();
	bfs();
	return 0;
}
