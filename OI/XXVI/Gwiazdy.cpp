#include<bits/stdc++.h>
#define N 500005
using namespace std;
int n, s, l[N], r[N], dif[N], ans[N], pom, korekta = 1e9, kdx, lewa_granica, prawa_granica, ile;
long long koszt;
pair<int,int> teleport[N];// ile - l/r 0/1
int idx = 1;

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>s;
	for(int i = 1; i < n; i++) {
		cin>>l[i]>>r[i];
		dif[i] = fabs(l[i] - r[i]);
	}
	
	if(l[1] < r[1]) teleport[1] = {1,0};
	else teleport[1] = {1,1};
	koszt += min(l[1], r[1]);
	
	for(int i = 2; i < n; i++)//wstepny plan
	{
		if(l[i] < r[i]) {
			if(teleport[idx].second == 0) teleport[idx].first++;
			else teleport[++idx] = {1,0};
		}
		else {
			if(teleport[idx].second == 1) teleport[idx].first++;
			else teleport[++idx] = {1,1};
		}
		koszt += min(l[i], r[i]);
	}
	
	if(teleport[1].second == 1 && teleport[1].first >= n - s + 1) { //trzeba korygowac
		pom = n - s + 1;//do tego czasu trzeba znalezc najtanszy zamiennik
		for(int i = 1; i <= pom; i++) if(dif[i] < korekta) {
			korekta = dif[i];
			kdx = i;
		}
		koszt += korekta;
		idx += 2;
		pom = teleport[1].first;
		for(int i = n - 1; i >= 2; i--) teleport[i + 2] = teleport[i];
		teleport[1] = {kdx - 1, 1};
		teleport[2] = {1,0};
		teleport[3] = {pom - kdx, 1};
		if(teleport[3].first == 0) {//zeby nie bylo sytuacji prawo(iles) lewo(1) prawo(0) lewo(..) bo wtedy zle sie zrobi sciezka, przesuniecie calego [4] do [2]
			teleport[2].first += teleport[4].first;
			teleport[4].first = 0;
		}
	}
	else if(teleport[1].second == 0 && teleport[1].first >= s) { //trzeba korygowac
		pom = s;//do tego czasu trzeba znalezc najtanszy zamiennik
		for(int i = 1; i <= pom; i++) if(dif[i] < korekta) {
			korekta = dif[i];
			kdx = i;
		}
		koszt += korekta;
		idx += 2;
		pom = teleport[1].first;
		for(int i = n - 1; i >= 2; i--) teleport[i + 2] = teleport[i];
		teleport[1] = {kdx - 1, 0};
		teleport[2] = {1, 1};
		teleport[3] = {pom - kdx, 0};
		if(teleport[3].first == 0) {//analogicznie
			teleport[2].first += teleport[4].first;
			teleport[4].first = 0;
		}
	}
	
	cout<<koszt<<"\n";
	cout<<s<<" ";
	
	lewa_granica = 1, prawa_granica = n;
	for(int tdx = 1; tdx <= idx; tdx++)
	{
		if(teleport[tdx].first == 0) continue;
		ile = teleport[tdx].first;
		if(teleport[tdx].second == 1)//prawo
		{
			int start = prawa_granica - ile + 1;
			if(s >= start && s <= prawa_granica) start--;
			for(int i = start; i <= prawa_granica; i++) 
			{
				if(i == s) continue;
				cout<<i<<" ";
			}
			prawa_granica = start - 1; 
		}
		if(teleport[tdx].second == 0)//lewo
		{
			int start = lewa_granica + ile - 1;
			if(s >= lewa_granica && s <= start) start++;
			for(int i = start; i >= lewa_granica; i--)
			{
				if(i == s) continue;
				cout<<i<<" ";
			}
			lewa_granica = start + 1;
		}
	}
	return 0;
}
