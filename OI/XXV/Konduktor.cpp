#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 500001
#define MOD 1000000007
#define INF 2000000000

int m, n, idx;
int dlugosc[2*N];		//dlugosci kolejnych sekcji
int nr_kontroli[2*N];	//kazda sekcja jesli znajduje sie w odcinku w ktorym musimy wykonac kontrole to ma zapamietany numer kontroli
int dp[2*N];			//stanem jest prefiks konczacy sie w sekcji w odcinku, w ktorym musimy wykonac kontrole, wynikiem jest ilosc sposobow wykonania kontroli w tym prefiksie uwzgledniajac wszystkie kontrole na prawo od nas
pii input[N];			//odcinki z wejscia

map<int,int> punkty;	//mapowanie punkt -> sekcja
vector<pii> odcinki;	//odcinki z wejscia bez niepotrzebnych odcinkow (takich ktore zawieraja calkowicie jakis inny odcinek)
int nast[N * 2]; 		//jesli w danej sekcji zrobie kontrole to w ktorej sekcji na prawo moge najpozniej zrobic nastepna kontrole (wazne przy liczeniu dynamika!)

void solve() {
	cin>>m>>n;
	punkty.clear();		
	odcinki.clear();
	rep(i,1,n) 
		cin>>input[i].f>>input[i].s;
	sort(input + 1, input + 1 + n);
	rep(i,1,n) {
		while(!odcinki.empty() && odcinki.back().f <= input[i].f && odcinki.back().s >= input[i].s)	//czyszczenie odcinkow wejsciowych z niepotrzebnych odcinkow
			odcinki.pop_back();
		odcinki.pb(input[i]);
	}
	n = odcinki.size();
	for(auto it: odcinki)
		punkty[it.f] = punkty[it.s] = 0;	//wstepne dodanie punktow do mapy
	int last = 0, sekcja = -1;
	for(auto &it: punkty) {		//pary postaci <punkt,numer sekcji>, dlugosc[numer sekcji] zwraca dlugosc tej sekcji
		if(sekcja != -1) 		//sekcje sa tylko pomiedzy punktami, dlatego przy kazdym punkcie dopiero przypisujemy dlugosc poprzedniej sekcji (przy ostatniem punkcie nie bedzie zadnej zaczynajacej sie sekcji)
			dlugosc[sekcja] = it.f - last;
		sekcja++;
		last = it.f;
		it.s = sekcja;
	}
	for(int i = 0; i < sekcja; i++)
		nr_kontroli[i] = -1; 
	last = INF;
	int kontrole = 0;
	vector<pii> rozwiazanie;													//odcinki na ktorych na pewno trzeba zrobic kontrole
	repv(i,n-1,0) {
		if(odcinki[i].s <= last) {												//liczymy minimalna liczbe kontroli (idziemy od konca wszystkich odcinkow)
			rozwiazanie.pb({punkty[odcinki[i].f], punkty[odcinki[i].s]});
			last = odcinki[i].f;
			int odkad = punkty[odcinki[i].f], dokad = punkty[odcinki[i].s];		//zaznaczamy tym odcinkow ze tam na pewno musi odbyc sie kontrola
			rep(j,odkad,dokad-1) 
				nr_kontroli[j] = kontrole;
			kontrole++;
		}
	}

	for(int i = 0; i < sekcja; i++)
		nast[i] = INF;
	for(auto it: odcinki) {
		int odkad = punkty[it.f], dokad = punkty[it.s];
		if(odkad != 0)
			nast[odkad-1] = min(nast[odkad-1], dokad-1);	//dla kazdego odcinka dla sekcji przed nim zaznaczamy ze jesli tam sie odbedzie kontrola to nastepna musi sie odbyc na koncu tego odcinka
	}
	for(int i = sekcja-2; i >= 0; i--)
		nast[i] = min(nast[i], nast[i+1]);					//zeby wszystkie sekcje byly wypelnione, bo tam wstepnie tylko dla sekcji przed odcinkami jest obliczone nast[], a w odcinkach bylo puste nast[]

	for (int i = 0; i < sekcja; ++i)
      dp[i] = 0;
	  
	dp[rozwiazanie[0].first] = dlugosc[rozwiazanie[0].f];
	for(int i = rozwiazanie[0].first + 1; i < rozwiazanie[0].second; i++) //dynamik dla poczatkowego odcinka, same dlugosci, niz wiecej
		dp[i] = dp[i-1] + dlugosc[i];
	
	for(int i = 1; i < rozwiazanie.size(); i++) {
		bool pierwszy = 1;
		for(int j = rozwiazanie[i].f; j < rozwiazanie[i].s; j++) {
			ll ile = 0;
			int nastepny = nast[j];
			if(nastepny != INF && nr_kontroli[j] == nr_kontroli[nastepny] + 1) //jesli wszystko sie zgadza to liczymy dynamika (dlugosc * dynamik od nastepnego miejsca)
				ile = (ll) dlugosc[j] * dp[nastepny] % MOD;
			if(!pierwszy) 										//dodajemy poprzednia sekcje (bo liczymy dynamika dla prefiksu)
				ile = (ile + dp[j-1]) % MOD;
			pierwszy = 0;
			dp[j] = ile;
		}
	}
	cout<<kontrole<<" "<<dp[punkty[odcinki[0].s]-1]<<"\n";//rozwiazaniem jest dynamik dla sekcji konczacej PIERWSZY odcinek (niekoniecznie pierwszy odcinek na ktorym trzeba zrobic kontrole!)
}

int main() {
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
