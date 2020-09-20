#include<bits/stdc++.h>
using namespace std;

struct item
{
	int c,a,b;
}przedmioty[1005];
struct query
{
	int m,k,s,idx;
}pytania[1000005];
class compare1
{
	public:
		bool operator()(const item& p1, const item& p2){
			return p1.a < p2.a;
		}
};
class compare2
{
	public:
		bool operator()(const query& q1, const query& q2){
			return q1.m < q2.m;
		}
};

int n, p, ans[1000005], dp[100005], INF = 1e9;//przedmioty, pytania, odpowiedzi tak/nie, "data waznosci" itej wartosci, INF

void dodaj(int i)//dodanie przedmiotu 
{
	int value = przedmioty[i].c, termin = przedmioty[i].b;
	for(int i = 100000; i >= value; i--){
		dp[i] = max(dp[i], min(dp[i - value], termin));
	}
}

void spytaj(int j)//spytanie czy mozna ukrasc
{
	if(dp[pytania[j].k] > pytania[j].m + pytania[j].s) ans[pytania[j].idx] = 1;
	else ans[pytania[j].idx] = 0;
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>przedmioty[i].c>>przedmioty[i].a>>przedmioty[i].b;
	}
	cin>>p;
	for(int i = 1; i <= p; i++){
		cin>>pytania[i].m>>pytania[i].k>>pytania[i].s;
		pytania[i].idx = i;//zeby w dobrej kolejnosci wypisac odpowiedzi!!!
	}
	
	sort(przedmioty + 1, przedmioty + 1 + n,compare1());//opowiednie posortowanie przedmiotow & pytan
	sort(pytania + 1, pytania + 1 + p,compare2());
	
	dp[0] = INF;//wartosc 0 ma waznosc nieskonczona
	int i = 1, j = 1;//indeksiki, i->przedmioty, j->pytania
	
	while(i <= n || j <= p){
		if(j == p + 1) break;//wszystkie pytania obsluzone!
		if(i == n + 1){//zostaly same pytania, mozna tylko spytac
			spytaj(j++);
			continue;
		}
		if(przedmioty[i].a <= pytania[j].m)	dodaj(i++);
		else spytaj(j++);
	}
	
	for(int i = 1; i <= p; i++) 
		if(ans[i]) cout<<"TAK\n";
		else cout<<"NIE\n";
	return 0;
}
