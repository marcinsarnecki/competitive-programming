#include<bits/stdc++.h>
#define N 100001
#define NTREE 131072

using namespace std;

int n, maks, pozycja;
int a[N], t[N], p[N];// klocek / ile jest dobrych zakladajac ze ity jest na czubku wiezy / miejsce z ktorego powiekszono wynik z przedzialu <1,i-1>
int tree[2 * NTREE];//drzwo max punkt-przedzial, wartosci sa z <1,1e6> wiec wyzerowane na starcie jest ok dla dzrewa typu max
vector<int> czystka;//ktore sa do wywalenia
int pom[N];//zamiana z wielkosci klocka na jego indeks, potrzebne przy odszukiwaniu indeksu liczby maksymalnej z pytania na drzewie przedzialowym

struct klocek
{
	int idx, a;
}order[N];

class compare
{
	public:
		bool operator()(const klocek &k1,const klocek &k2)
		{
			if(k1.idx - k1.a == k2.idx - k2.a) return k1.a < k2.a;
			return k1.idx - k1.a < k2.idx - k2.a;
		}
};

void insert(int value, int pos)
{
	pos += NTREE;
	if(value > tree[pos])
	{
		tree[pos] = value;
		pos /= 2;
		while(pos)
		{
			tree[pos] = max(tree[pos * 2], tree[pos * 2 + 1]);
			pos /= 2;
		}
	}
}

pair<int,int> query(int a, int b)//para wartosc - pozycja gdzie ona jest (potrzebne)
{
	int p = a + NTREE;
	int k = b + NTREE;
	if(p > k) return make_pair(0,0);
	if(p == k) return make_pair(tree[p], p - NTREE);
	int ans = tree[p], pos = p;
	if(ans < tree[k]) {
		ans = tree[k];
		pos = k;
	}
	while(k - p > 1)
	{
		//if(k % 2 == 1) ans = max(ans, tree[k - 1]);
		if(k % 2 == 1) if(ans < tree[k - 1]) {
			ans = tree[k - 1];
			pos = k - 1;
		}
		//if(p % 2 == 0) ans = max(ans, tree[p + 1]);
		if(p % 2 == 0) if(ans < tree[p + 1]) {
			ans = tree[p + 1];
			pos = p + 1;
		}
		p /= 2;
		k /= 2;
	}
	//pos to wezel, w ktorym znajduje sie maksymalny lisc
	while(pos < NTREE)
	{
		if(tree[pos * 2] == ans) pos *= 2;
		else pos = (pos * 2) + 1;
	}
	if(ans == 0) return make_pair(0,0);
	return make_pair(ans, pos - NTREE);
}

int main()
{
	//t[i] - najwieksza ilosc klockow zgadzjaca sie jesli budujemy wieze do i oraz i jest na szczycie
	//dla kazdego klocka 'i' szukamy najwiekszego takiego j < i zeby a[j] < a[i] oraz i - j >= a[i] - a[j] (zeby przy usuwaniu klockow z wiezy sie tam zgadzalo wszystko)
	//dzieki sortowaniu mamy warunek 3, warunek 2 jest zachowany dzieki odpowiednim operacjom na drzewie, patrzymy na max z <1,a[i]),a potem wstawiamy t[i] na pozycje a[i]
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++){
		cin>>a[i];
		order[i].a = a[i];
		order[i].idx = i;
	}
	sort(order + 1, order + 1 + n,compare());//sortowanie, biorac po kolei spelniamy warunek II
	for(int i = 1; i <= n; i++)
	{
		if(order[i].a > order[i].idx) t[order[i].idx] = 0;//i tak nic sie nie da zrobic
		if(order[i].a <= order[i].idx)//klocek mniejszy rowny swojej pozycji
		{
			pair<int,int> z = query(1, order[i].a - 1);//tutaj korzystac bedziemy z warunku III
			int v = z.first;
			int pos = z.second;
			t[order[i].idx] = v + 1;
			p[order[i].idx] = pom[pos];//pom musi byc bo samo pos to pozycja w drzewie, w drzewie jest wielkosc klocka a my chcemy jego indeks
			insert(v + 1, order[i].a);
			pom[order[i].a] = order[i].idx;//potrzebne, to tylko drobnostka w kodzie, nie zmienia to pomyslu algorytmu
		} 
	}
	for(int i = 1; i <= n; i++) if(maks < t[i]){
		maks = t[i];
		pozycja = i;
	}
	while(t[pozycja])
	{
		//wywal (i - j) - (ai - aj) klockow z przedzialu (j,i)
		int i = pozycja, j = p[pozycja];
		for(int ii = j + 1, l = 1; l <= (i - j) - (a[i] - a[j]); ii++,l++) czystka.push_back(ii);
		pozycja = j;
	}
	sort(czystka.begin(),czystka.end());
	cout<<czystka.size()<<"\n";
	for(int i = 0; i < czystka.size(); i++) cout<<czystka[i]<<" ";
	return 0;
}
