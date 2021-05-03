#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = 1e18;

#define N 100001
#define A_MAX 58

int n, zap[N];
ll a[100];

map<ll, pii> ans;
set<ll> all;
vector<ll> saved; 

void wczytaj() {
    cin>>n;
    rep(i,1,n)
        cin>>zap[i];
}

int mex() { //najmniejsza liczba nienalezaca do zbioru
    int i = 1;
    while(1) {
        if(all.find(i) == all.end())
            return i;
        i++;
    }
}

int korekta(int x) {//ile jest zapisanych wynikow pomiedzy 54 a x (potrzebne przy liczeniu wyniku dla liczb, ktore nie sa roznica dwóch z 58 poczatkowych wyrazow ciagu a)
    return upper_bound(saved.begin(), saved.end(), x) - upper_bound(saved.begin(), saved.end(), 54);
}

void init() {//pierwsze 58 wyrazow ciagu a (a[58] = 2124567664, ponad 2 mld) oraz zapisanie wszystkich roznic do mapy 
    a[1] = 1;
    a[2] = 2;
    all.insert(1);
    all.insert(2);
    rep(i,3,A_MAX) {
        if(i % 2 == 1) {
            a[i] = a[i-1] * 2;
            repv(j,i-1,1)
                all.insert(a[i] - a[j]);
        }
        if(i % 2 == 0) {
            int d = mex();
            a[i] = a[i-1] + d;
            repv(j,i-1,1)
                all.insert(a[i] - a[j]);
        }
    }    
    rep(i,1,A_MAX)
        rep(j,i+1,A_MAX) 
            ans[a[j]-a[i]] = {j,i};//zapamietanie wszystkich "latwych" odpowiedzi 

    saved.pb(-INF);//potrzeba bedzie szybko odpowiadac na zapytania ile jest liczb w mapie z odpowiedziami pomiedzy 54 a zapytaniem, wiec zapisuje je do vectora i potem roznica upper boundow
    for(auto it: ans) 
        saved.pb(it.f);
    saved.pb(INF);//dla bezpieczenstwa nieskonczonosci na krancach
}

void solve() {
    rep(i,1,n) {
        int x = zap[i];
        if(all.find(x) != all.end()) { //jesli odpowiedz jest spamietana to od razu wypisujemy
            pii it = ans[x];
            cout<<it.f<<" "<<it.s<<"\n";
        }
        else {
            int k = korekta(x);         //jesli tej liczby nie bylo w mapie to trzeba policzyc miejsce w ciagu gdzie ona zostanie uzyta jako roznica dwoch kolejnych elementow
            int r = 58 + (x-54-k) * 2;  //do liczby 54 wszystkie sa zapamietane, jesli x nie ma w mapie to musi on byc >54, ans[54] = {58,57} wiec do 58 wystarczy dodac 
            cout<<r<<" "<<r-1<<"\n";    //roznice x i 54 skorygowana o to ile miedzy nimi jest liczb na ktore jest latwa odpowiedz, bo one nie zostana uzyte dalej w ciagu jako roznica dwoch kolejnych elementow
        }
    }
}

int main()
{
	ios_base::sync_with_stdio(0);
	wczytaj();
  init();
  solve();
	return 0;
}
