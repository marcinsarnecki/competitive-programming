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

list< pii > kmax; //para wartosc-indeks
list< pii > kmin;

void dodaj_max(int v,int odl)
{
	while(!kmax.empty() && kmax.back().first <= v)	kmax.pop_back();
	kmax.push_back({v,odl});
}

void dodaj_min(int v,int odl)
{
	while(!kmin.empty() && kmin.back().first >= v)	kmin.pop_back();
	kmin.push_back({v,odl});
}

int maks()
{
	if(!kmax.empty()) return (kmax.front()).first;
	return 0;
}

int mini()
{
	if(!kmin.empty()) return (kmin.front()).first;
	return 0;	
}

void usun_max(int odl)
{
	if( kmax.front().second==odl ) kmax.pop_front();
}

void usun_min(int odl)
{
	if( kmin.front().second==odl ) kmin.pop_front();
}

int main()
{
	ios_base::sync_with_stdio(0);
	return 0;
}
