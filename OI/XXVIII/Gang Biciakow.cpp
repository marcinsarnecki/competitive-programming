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

#define N 100001
#define M 150001

int n, m, q, p, temp[N], tempbiciak[N], preorder[N], postorder[N], parent[N], ldx, ans[M];
int biciak[N];//w danym wierzcholku jaki biciak
int rozne, ile[M];//ile roznych biciakow na sciezce (czyli aktualna odpowiedz), [] tablica do zliczania biciakow na sciezce
bool sciezka[N];//czy dany wierzcholek znajduje sie na aktualnej sciezce
vector<int> graf[N];
pii kraw[N];//krawedzie z wejscia
pair<int,pii> zap[M];//pytania i aktualizacje z wejscia
int ed[N], edx;//moment odwiedzenia wierzcholka w przejsciu Eulera

pii zmiany[M], cofnij[M];//zmiany w czasie <wierzcholek, biciak>, cofniecie danej zmiany (poprzedni biciak w danym miejscu)
int tdx, adx;//liczniki do zmian i zapytan

struct event{//zapytanie w postaci wydarzenia (zeby je uporzadkowac i uzyskac optymalna zlozonosc czasowa)
	int t, x, v, id;//czas, odleglosc z przejscia eulera, wierzcholek, nr zapytania
};

vector<event> kubelki[500];	//kubelki na warstwy w 2d przestrzeni punktow (zapytan)
							//o wspolrzednych postaci <czas (ilosc dotychczasowych zmian), moment odwiedzenia wierzcholka w przejsciu eulera>

bool compare(const event& e1, const event& e2) {
	return e1.x < e2.x;
}

void dodaj(int v) { //dodanie wierzcholka v do sciezki
	sciezka[v] = 1;
	if(++ile[biciak[v]] == 1)
		rozne++;
}

void usun(int v) { //usuniecie wierzcholka v ze sciezki
	sciezka[v] = 0;
	if(--ile[biciak[v]] == 0)
		rozne--;
}

void zmien(int v, int c) {//zmiana biciaka w danym wierzcholku
	if(biciak[v] == c) //zmiana na ten sam rodzaj biciaka, nic sie nie dzieje
		return;
	if(sciezka[v]) { //dany wierzcholek znajduje sie na naszej sciezce
		usun(v);	//usuwamy go
		biciak[v] = c;//zmieniamy
		dodaj(v);	//dodajemy
	}
	else //jesli wierzcholka nie ma na sciezce to po prostu zmieniamy mu biciaka i nic wiecej nie robimy
		biciak[v] = c;
}

void input() {
	cin>>n>>m>>q;
	rep(i,1,n-1) {
		int a, b, c;
		cin>>a>>b>>c;
		graf[a].pb(b);
		graf[b].pb(a);
		kraw[i] = {a,b};
		temp[i] = c;
	}
	rep(i,1,q) {//Z x // B i c
		char z;
		cin>>z;
		if(z == 'Z') {
			int x;
			cin>>x;
			zap[i] = {1,{x,0}};
		}
		if(z == 'B') {
			int nr, c;
			cin>>nr>>c;
			zap[i] = {0,{nr,c}};
		}
	}
}

bool przodek(int v, int u) {
	return (preorder[v] <= preorder[u] && postorder[v] >= postorder[u]);
}

void dfs(int v, int prev) {
	preorder[v] = ldx++;
	ed[v] = edx;
	parent[v] = prev;
	for(auto u: graf[v])
		if(u != prev) {
			edx++;
			dfs(u, v);
		}
	postorder[v] = ldx++;
	edx++;
}

void przejdz(int v1, int v2) {//majac sciezke konczaca sie w v1 chcemy przejsc do wierzcholka v2
	if(v1 == v2)
		return;
	while(!przodek(v1,v2)) {
		usun(v1);
		v1 = parent[v1];
	}
	while(!przodek(v2,v1)) {
		dodaj(v2);
		v2 = parent[v2];
	}
}

void init() {
	dfs(1,0);
	rep(i,1,n-1) //uporzadkowanie wierzcholkow w krawedziach tak, aby ten pierwszy byl przodkiem tego drugiego
		if(przodek(kraw[i].s, kraw[i].f)) {
			int c = kraw[i].f;
			kraw[i].f = kraw[i].s;
			kraw[i].s = c;
		}
	rep(i,1,n-1) //biciaki juz istniejace
		biciak[kraw[i].s] = temp[i];
	rep(i,2,n)
		tempbiciak[i] = biciak[i];
	rep(i,1,q) //zeby w zapytaniach zamiast nr drogi byl nr wierzcholka
		if(zap[i].f == 0) 
			zap[i].s.f = kraw[zap[i].s.f].s;
	p = sqrt(n + q);
}

void solve() {
	int currentV = 1, currentT = 0;//aktualny wierzcholek i czas (zmiana)
	rep(i,1,q) {
		if(zap[i].f == 0) 
			zmiany[++tdx] = zap[i].s;
		if(zap[i].f == 1) {
			int v = zap[i].s.f, t = tdx / p;
			kubelki[t].pb({tdx,ed[v],v,++adx});
		}
	}
	rep(i,1,tdx) {
		int v = zmiany[i].f;
		cofnij[i] = {v,tempbiciak[v]};
		tempbiciak[v] = zmiany[i].s;
	}
	rep(i,0,499)
		sort(kubelki[i].begin(), kubelki[i].end(), compare);//zapytania w kubelkach sortujemy po momentach odwiedzenia w przejsciu eulera
	rep(k,0,499)
		for(auto e: kubelki[k]) {
			int v = e.v, t = e.t, id = e.id;
			if(currentT < t)//trzeba uwzglednic wiecej zmian, idziemy do przodu w czasie (zmianach biciakow)
				for(int i = currentT + 1; i <= t; i++)
					zmien(zmiany[i].f,zmiany[i].s);
			if(currentT > t)//za duzo zmian, cofamy sie w zmianach biciakow
				for(int i = currentT; i > t; i--)
					zmien(cofnij[i].f,cofnij[i].s);//tutaj przydaje sie cofnij[] ktore pamieta biciaki przed dana zmiana
			currentT = t;
			przejdz(currentV, v);
			ans[id] = rozne;//odpowiedzia jest oczywiscie ilosc roznych biciakow
			currentV = v;
		}
	rep(i,1,adx)
		cout<<ans[i]<<"\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	input();
	init();
	solve();
	return 0;
}
