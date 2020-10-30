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

#define N 200001

ll N1, N2;//ile domin dodatkowych
int H1, H2;//wysokosci dodatkowych domin
int ir;//iloraz H1 / H2

int n;//podstawowe dane
ll x[N], MAX_x;
int h[N];
ll Ans;

pair<ll,ll> eff[N];//x, zasieg (dla efektywnych przedzialow domin)
int idx, ileeff[N];//ile sie zbija dla eff[] //idx to ilosc efektywnych

ll ileH1[N], ileH2[N];//ile potrzeba H1 do wstepnego wypelnienia dziury po eff[], ile h2 potrzeba do pelnego wypelnienia
ll neededH1, neededH2;//sumujemy ile H1 i H2 potrzebnych na naszym przedziale
ll currentSumEff, availableH1, availableH2;

#define NTREE 1048576
int iletree[2*NTREE];
ll sumtree[2*NTREE];

void update(int num, int add) {//add 1 dodaje, -1 odejmuje
	int pos = num + NTREE;
	num *= add;
	while(pos) {
		sumtree[pos] += num;
		iletree[pos] += add;
		pos /= 2;
	}
}

ll query(int v, int k) {//k najwiekszych
	if(sumtree[v] == 0) return 0;
	if(iletree[v] == k)
		return sumtree[v];
	if(v >= NTREE) {
		return sumtree[v] / iletree[v] * k;
	}
	int ile2 = iletree[2 * v + 1];//ile jest w prawym synie
	if(k > ile2) return query(2 * v, k - ile2) + query(2 * v + 1, ile2); 
	return query(2 * v + 1, k);
}

void wej() {
	cin>>n;
	rep(i,1,n) {
		cin>>x[i]>>h[i];
		MAX_x = max(MAX_x, x[i]);
	}
	cin>>N1>>H1>>N2>>H2;
	if(H1 < H2) {
		swap(H1,H2);
		swap(N1,N2);
	}
	ir = H1 / H2;//iloraz
}

void init() {
	idx = 1;
	eff[1].f = x[1];
	eff[1].s = x[1] + h[1];
	ileeff[1] = 1;
	rep(i,2,n) {
		if(x[i] <= eff[idx].s) {
			eff[idx].s = max(eff[idx].s, x[i] + h[i]);
		}
		else {
			idx++;
			eff[idx].f = x[i];
			eff[idx].s = x[i] + h[i];
		}
		ileeff[idx]++;
	}
	rep(i,1,idx - 1) {
		ll dif = eff[i + 1].f - eff[i].s;//odleglosc miedzy efektywnymi
		ileH1[i] = dif / H1;
		dif %= H1;
		ileH2[i] = dif / H2;
		dif %= H2;
		if(dif != 0) ileH2[i]++;
	}
}

bool check(int left, int right) {
	availableH1 = N1, availableH2 = N2;
	if(availableH1 >= neededH1) {
		availableH1 -= neededH1;
		if(availableH1 >= right - left) //jest tyle H1 że na luzie wystarcza bez kombinowania
			return true;
		ll sumQuery = query(1, availableH1);
		if(availableH2 >= neededH2 - sumQuery) //bez k najwiekszych wystarcza nam H2
			return true;
		else
			return false;
	}
	else {
		if(availableH2 >= neededH2 + (neededH1 - availableH1) * ir) // czy dostepne H2 wystarcza na pokrycie wszystkiego
			return true;											// (H1 * ir) wyjdzie ile H2 potrzeba na podstawowe
		else 														// wypelnienie tego co powinno H1 wypelnic
			return false;
	}
	
}

void solve() {//gasienica typu push right, i popraw left
	int left = 1, right = 1;
	currentSumEff = ileeff[1];
	neededH1 = 0, neededH2 = 0;
	Ans = max(Ans, currentSumEff + N1 + N2);
	while(right < idx) {
		neededH1 += ileH1[right];
		neededH2 += ileH2[right];
		update(ileH2[right], 1);
		right++;
		currentSumEff += ileeff[right];
		while(check(left,right) == 0) {//korekta
			neededH1 -= ileH1[left];
			neededH2 -= ileH2[left];
			update(ileH2[left], -1);
			currentSumEff -= ileeff[left];
			left++;
		}
		Ans = max(Ans, currentSumEff + N1 + N2);
	}
	rep(i,left,right - 1) update(ileH2[i], -1);
}

void odwroc() {
	rep(i,1,n) {
		x[i] *= -1;
		x[i] += MAX_x;
	}
	reverse(x + 1, x + 1 + n);
	reverse(h + 1, h + 1 + n);
}

void czystka() {
	rep(i,1,n) 
		ileH1[i] = ileH2[i] = ileeff[i] = eff[i].f = eff[i].s = 0;
	currentSumEff = neededH1 = neededH2 = 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	wej();
	init();
	solve();
	odwroc();
	czystka();
	init();
	solve();
	cout<<Ans;
	return 0;
}
