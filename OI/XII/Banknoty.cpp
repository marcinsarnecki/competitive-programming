#include<bits/stdc++.h>
using namespace std;
int n, k, inf = 1000000000;
int R[201][20001], W[201][20001], b[201], c[201];
list<pair<int,int> > kolejka;//styl <indeks,R>

void dodaj(int l,int wartosc)
{
	//while(!kolejka.empty() && kolejka.back().second - kolejka.back().first >= wartosc - l) kolejka.pop_back();
	while(!kolejka.empty() && wartosc - kolejka.back().second <= l - kolejka.back().first) kolejka.pop_back();//l - first to ile banknotow do minimum, wartosc - second to roznica w banknotach, jak jest wieksza badz rowna to lepiej zmienic na nowy
																											//nasza wartosc musi byc < badz = l - first + tamta wartosc
	kolejka.push_back({l, wartosc});
}

void usun(int l)
{
	if(!kolejka.empty() && kolejka.front().first == l) kolejka.pop_front();
}

void czysc()
{
	while(kolejka.size()) kolejka.pop_back();
}

int main()
{
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>b[i];
	for(int i = 1; i <= n; i++) cin>>c[i];
	cin>>k;
	for(int i = 0; i <= n; i++) for(int j = 1; j <= k; j++) R[i][j] = inf;
	for(int i = 1; i <= n; i++){
//		cout<<"jestem w i = "<<i<<"\n";
		for(int s = 0; s < b[i]; s++){
			czysc();
//			cout<<"s = "<<s<<" ";
			for(int licznik = 0; s + licznik * b[i] <= k; licznik++){
				dodaj(licznik, R[i - 1][s + licznik * b[i]]);
//				cout<<"dodaje "<<licznik<<" "<<R[i - 1][s + licznik * b[i]]<<"\n";
				int wartosc = kolejka.front().second, l = kolejka.front().first;
//				cout<<"zdjalem z kolejki l = "<<l<<" wartosc = "<<wartosc<<"\n";
				usun(licznik - c[i]);
				R[i][s + licznik * b[i]] = wartosc + licznik - l;
				W[i][s + licznik * b[i]] = licznik - l;
			}
		}	
	}
	cout<<R[n][k]<<"\n";
	int j = k;
	vector<int> v;
	for(int i = n; i >= 1; i--) {
		v.push_back(W[i][j]);
		j -= W[i][j] * b[i];
	}
	for(int i = v.size() - 1; i >= 0; i--) cout<<v[i]<<" ";	
/*	cout<<"R[n][k]:\n";
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= k; j++) cout<<R[i][j]<<" ";
		cout<<"\n";
	}
	cout<<"W[n][k]:\n";
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= k; j++) cout<<W[i][j]<<" ";
		cout<<"\n";
	}*/
	return 0;
}
