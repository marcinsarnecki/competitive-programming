#include<bits/stdc++.h>//rozwiazanie zachlanne, po kolei od najmniejszych dobierac (z sortowaniem), niepotrzebne scalic w wieksze bo byc moze uzyska sie jakies lepsze wieksze pudelko
using namespace std;
int n,q,ans;//pudelka,kontenery,wynik
vector<int> pudelka[1005];//w vectorze [i] sa wartosci pudelek rozmiaru i
int kontenery[1005];//ilosc kontenerow danego rozmiaru
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++){
		int wartosc, rozmiar;
		cin>>rozmiar>>wartosc;
		pudelka[rozmiar].push_back(wartosc);
	}
	cin>>q;
	for(int i = 1; i <= q; i++){
		int rozmiar, ile;
		cin>>rozmiar>>ile;
		kontenery[rozmiar] = ile;
	}
	for(int i = 0; i <= 1000; i++){//po kolei po wszystkich rozmiarach 
		if(pudelka[i].size() < kontenery[i]){//za malo pudelek aby wgl wypelnic kontenery czymkolwiek, koniec programu
			cout<<"NIE";
			return 0;
		}
		sort(pudelka[i].begin(),pudelka[i].end());
		int idx = 0;
		if(kontenery[i] > 0){//dobiera najmniejsze pudelka do wypelnienia kontenerow i zapisuje w wyniku
			for(;idx < kontenery[i]; idx++){
				ans += pudelka[i][idx];
			}
		}
		for(;idx + 1 < pudelka[i].size(); idx += 2){//scala dwa niepotrzebne mniejsze pudelka w jeden wiekszy, byc moze nowe pudelko bedzie mialo mniejsza wartosc od tych wiekszych
			pudelka[i + 1].push_back(pudelka[i][idx] + pudelka[i][idx + 1]);
		}
	}
	cout<<ans;
	return  0;
}
