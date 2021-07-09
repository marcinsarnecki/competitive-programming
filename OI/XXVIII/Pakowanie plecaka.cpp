#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = (ll)1e18;

#define N 500001
#define NTREE 524288

vector<ll> ans;     //rozwiazanie polega na odwtorzeniu listy przedmiotow od konca
vector<int> items;  //wiemy, ze w ostatnim plecaku musza znalezc sie wszystkie przedmioty
ll sum;             //teraz w kazdym kroku bedziemy szukali przedmiotu, ktory nie znajdzie sie w optymalnym plecaku rozmiar mniejszym od aktualnego
int n, a[N];        //chcemy wyrzucic oczywiscie przedmiot jak najwiekszy, aby nastepne plecaki byly jak najmniejsze
                    //kluczowa obserwacja: wyrzucany przedmiot > suma pozostalych przedmiotow na prawo od niego (no bo inaczej bysmy go i tak wzieli, a nie wyrzucili)
                    //ze wszystkich "dostepnych" przedmiotow wybieramy ten najbardziej na lewo, poniewaz jest on wiekszy od innych dostepnych
                    //wystarczy drzewo przedzialowe dodajace sume na przedziale i wyszukujace pierwszy element > 0
ll tree[2*NTREE], lazy[2*NTREE]; // drzewo (+,max), aktualizacja sumy na przedziale, pytanie o miejsce pierwszej dodatniej liczbe od lewej 

void update(int v, int start, int end, int l, int r, ll value) {
    if(lazy[v] != 0) {
        tree[v] += lazy[v];
        if(start != end) {
            lazy[2*v] += lazy[v];
            lazy[2*v+1] += lazy[v];
        }
        lazy[v] = 0;
    }

    if(start > r || end < l || start > end)
		return;

    if(start >= l && end <= r) {
		tree[v] += value;
		if(start != end) {
			lazy[v * 2] += value;
			lazy[2 * v + 1] += value;
		}
		return;
	}

    int mid = (start + end) / 2;
    update(2 * v, start, mid, l, r, value);
	update(2 * v + 1, mid + 1, end, l , r, value);
	tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int query(int v) { //miejsce pierwszej dodatniej liczby 
    if(v >= NTREE) //jesli jestesmy w lisciu to zwracamy pozycje z ciagu
        return v - NTREE;
    if(lazy[v] != 0) { 
        tree[v] += lazy[v];
        lazy[2*v] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    if(tree[2*v] + lazy[2*v] > 0) //jesli w lewym synie znajduje sie dodatnia liczby to idziemy tam
        return query(2*v);
    return query(2*v+1); //a jesli nie to idziemy do prawego syna
}

void wczytaj() {
	cin>>n;
    rep(i,1,n) {
        cin>>a[i];
        sum += a[i];
    }
}

void init() {
    rep(i,1,n) 
        tree[i+NTREE] = a[i];
    repv(i,NTREE-1,1)
        tree[i] = max(tree[2*i], tree[2*i+1]);//poczatkowe wypelnienie drzewa wartosciami z ciagu
    rep(i,2,n)
        update(1,0,NTREE-1,1,i-1,-a[i]);//dodanie wartosci -a_i na przedziale <1,i-1>
}

void solve() {
    rep(i,1,n-1) {
        int idx = query(1); //szukamy pierwszej dodatniej liczby
        items.pb(a[idx]); //dodajemy przedmiot
        if(idx > 1)
            update(1,0,NTREE-1,1,idx-1,a[idx]);
        update(1,0,NTREE-1,idx,idx,-INF); //czyscimy dane miejsce minus nieskonczonoscia
    }
    ans.pb(sum);
    for(auto it: items) {//majac przedmioty dodawane od konca odtwarzamy wynik
        sum -= it;
        ans.pb(sum);
    }
    reverse(ans.begin(), ans.end());
    for(auto it: ans)
        cout<<it<<" ";
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
  init();
	solve();
	return 0;
}
