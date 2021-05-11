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

#define N 200001

int n;
pii w[N], wstepnie[N];//wejsciowe wektory, wstepnie posortowane
pii sorted[N];//wektory o tym samym kierunku i zwrocie sa zsumowane do pojedynczego wektora
ll ans;

ll iloczynWektorowy(const pii& a, const pii& b) {
	return ((ll)a.f * b.s) - ((ll)a.s * b.f); 
}

ll iloczynSkalarny(const pii& a, const pii& b) {
	return ((ll)a.f * b.f) + ((ll)a.s * b.s); 
}

bool compare(pair<int,int>& a, pair<int,int>& b) {
	return ((double)a.f/a.s)<((double)b.f/b.s);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	rep(i,1,n) 
		cin>>w[i].f>>w[i].s; 
	 
	pii gora,prawo,dol,lewo;
	vector< pair<int,int> > I,II,III,IV;
	
	rep(i,1,n)
	{
		if(w[i].f==0)
		{
			if(w[i].s>0) gora.s += w[i].s;
			if(w[i].s<0) dol.s += w[i].s;
		}
		else if(w[i].s==0)
		{
			if(w[i].f>0) prawo.f += w[i].f;
			if(w[i].f<0) lewo.f += w[i].f;
		}
		if(w[i].f>0)
		{
			if(w[i].s>0) I.push_back(w[i]);
			if(w[i].s<0) II.push_back(w[i]);
		}
		else if(w[i].f<0)
		{
			if(w[i].s<0) III.push_back(w[i]);
			if(w[i].s>0) IV.push_back(w[i]); 
		}
	}
	sort(I.begin(),I.end(),compare);
	sort(II.begin(),II.end(),compare);
	sort(III.begin(),III.end(),compare);
	sort(IV.begin(),IV.end(),compare);
	int nr=0;
	if(gora.s != 0) wstepnie[nr++] = gora;
	for(int i=0;i<I.size();i++) wstepnie[nr++]=I[i];
	if(prawo.f != 0) wstepnie[nr++] = prawo;
	for(int i=0;i<II.size();i++) wstepnie[nr++]=II[i];  
	if(dol.s != 0) wstepnie[nr++] = dol;
	for(int i=0;i<III.size();i++) wstepnie[nr++]=III[i];
	if(lewo.f != 0) wstepnie[nr++] = lewo;
	for(int i=0;i<IV.size();i++) wstepnie[nr++]=IV[i];

	int idx = 0;
	sorted[0] = wstepnie[0];
	for(int i = 1; i < nr; i++) {
		if(iloczynWektorowy(sorted[idx], wstepnie[i]) == 0 && iloczynSkalarny(sorted[idx], wstepnie[i]) > 0) {//dwa wektory maja ten sam kierunek jesli wektorowy = 0, trzeba jeszcze sprawdzic skalarny > 0 bo moga miec przeciwne zwroty
			sorted[idx].f += wstepnie[i].f;
			sorted[idx].s += wstepnie[i].s;
		}
		else 
			sorted[++idx] = wstepnie[i];
	}
	// sorted[0,idx] zwiera posortowane zgodnie z ruchem wskazowek zegara rozpoczynajac od wektora (0,y+)
	int j = 0;
	pii suma = {0,0};
	rep(i,0,idx) {//plaszczyzny zawierajace wektor w swojej lewej polprostej
		while(iloczynWektorowy(sorted[i],sorted[j]) <= 0) {
			suma.f += sorted[j].f;
			suma.s += sorted[j].s;
			j = (j == idx+1) ? 0 : j+1;
			if(i == j) 
				break;
		}
		ans = max(ans, iloczynSkalarny(suma, suma));

		suma.f -= sorted[i].f;
		suma.s -= sorted[i].s;
		ans = max(ans, iloczynSkalarny(suma, suma));//odrobine przesunieta plaszczyzna
	}
	j = idx;
	suma = {0,0};
	repv(i,idx,0) {//plaszczyzny zawierajace wektor w swojej prawej polprostej
		while(iloczynWektorowy(sorted[i],sorted[j]) >= 0) {
			suma.f += sorted[j].f;
			suma.s += sorted[j].s;
			j = (j == -1) ? idx : j-1;
			if(i == j) 
				break;
		}
		ans = max(ans, iloczynSkalarny(suma, suma));

		suma.f -= sorted[i].f;
		suma.s -= sorted[i].s;
		ans = max(ans, iloczynSkalarny(suma, suma));
	}
	cout<<ans;		
	return 0;
}
