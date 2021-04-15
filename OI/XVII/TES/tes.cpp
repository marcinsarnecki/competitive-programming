#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

#define N 1000001
#define INF 10000000
vector<int> wystapienia[N];
int tab[N], n, m, ile, granica, b[N];

int nastepny(int num, int g) {//w liczbie 'num' pierwsze wystapienie na pozycji wiekszej niz 'g'
	if(g == INF)
		return INF;
	if(wystapienia[num].size()==0) //jesli tej liczby wgl nie ma to zwracamy INF 
		return INF; 
	int l = 0, r = wystapienia[num].size() - 1, mid;
	while(l <= r) { //binsearch
		mid = (l + r) / 2;
		if(wystapienia[num][mid] > g)
			r = mid - 1;
		else
			l = mid + 1;
	}
	return wystapienia[num][r+1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin>>m;
	rep(i,1,m) {
		cin>>tab[i];
		if(wystapienia[tab[i]].size() == 0) //dla kazdej liczby ktora sie pojawi na wejsciu dodajemy na poczatku -1 do wystapien
			wystapienia[tab[i]].pb(-1);		
		wystapienia[tab[i]].pb(i);
	}
	rep(i,1,m)
		wystapienia[tab[i]].pb(INF);//INF na koniec vectora z wystapieniami dla kazdej liczby ktora pojawila sie na wejsciu
	  cin>>n;
	rep(i,1,n) {
		cin>>ile;
		granica = 0;
		rep(j,1,ile)
			cin>>b[j];
		rep(j,1,ile) //granica oznacza w ktorym miejscu skonczylismy, i tak dla kazdej kolejnej liczby obliczamy jej pierwsze wystapienie wieksze niz granica
			granica = nastepny(b[j], granica);
		if(granica != INF) //jesli nie wyladowalismy w nieskonczonosci to znaczy ze odpowiedz istnieje
			cout<<"TAK\n";
		else
			cout<<"NIE\n";
	}
	return 0;
}
