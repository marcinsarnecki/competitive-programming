#include<bits/stdc++.h>
using namespace std;
int n, tab[1000005], idx, idy, idr, wynik;
int pref[1000005], suf[1000005];
vector<int> wyst[27];
int main()
{
	ios_base::sync_with_stdio(0);
	
	cin>>n;
	for(int i = 1; i <= n; i++) {
		char z;
		cin>>z;
		wyst[z - 96].push_back(i);
	}
	
	for(int i = 1; i <= 26; i++)
		for(int j = 1; j <= 26; j++) {//kazda literka z kazda literka
			if(i == j) continue;//nie sprawdzamy tej samej literki z ta sama literka
			if(wyst[i].size() == 0) continue;
			if(wyst[j].size() == 0) continue;//jesli jedna ze sprawdzanych literek nie ma zadnych wystapien - continue
			idx = idy = idr = 0;//x y jada po vectorach wystapien dwoch literek, r buduje pomocnicza tablice +1 -1 wystapien literek
			while(idx < wyst[i].size() || idy < wyst[j].size())
			{
				if(idx == wyst[i].size()) 
				{
					tab[++idr] = -1;
					idy++;
				}
				else if(idy == wyst[j].size()) 
				{
					tab[++idr] = 1;
					idx++;
				}
				else 
				{
					if(wyst[i][idx] < wyst[j][idy]) 
					{
						tab[++idr] = 1;
						idx++;
					}
					else
					{
						tab[++idr] = -1;
						idy++;
					}
				}
			}
			int sum = 0;
			for(int i = 1; i <= idr; i++) 
			{
				sum += tab[i];
				if(sum < 0) sum = 0;
				pref[i] = sum;
			}
			sum = 0;
			for(int i = idr; i >= 0; i--) 
			{
				sum += tab[i];
				if(sum < 0) sum = 0;
				suf[i] = sum;
			}
			suf[idr + 1] = 0;//brzeg 
			for(int i = 1; i <= idr; i++) //w szukanym przedziale musi byc przynajmniej jedna druga literka wiec szukamy wyniku patrzac na -1 i z boku max podtablica z lewej i prawej
				if(tab[i] == -1) wynik = max(wynik, pref[i - 1] - 1 + suf[i + 1]);
		}
	cout<<wynik;

	return 0;
}
