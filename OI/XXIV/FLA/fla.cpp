#include<bits/stdc++.h>
#define N 500001
using namespace std;
struct przeszkoda
{
	int x,a,b,maks,mini,k;//k to koszt na mini, dla maks to bedzie k + 1/2*(maks-mini)
}p[N];
int n,X,koszt;
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>X;//start to przeszkoda 0 ze wszystkimi parametrami = 0;
	for(int i = 1; i <= n; i++) 
	{
		cin>>p[i].x>>p[i].a>>p[i].b;
		p[i].a++;
		p[i].b--;
	}
	for(int i = 1; i <= n; i++) 
	{
		int d = p[i].x-p[i-1].x;//dystans miedzy przeszkodami
		int gora = p[i-1].maks + d;
		int dol = p[i-1].mini - d;
		
		if(gora<p[i].a||dol>p[i].b) {
			cout<<"NIE";
			return 0;
		}
		
		if(gora > p[i].b) {
			if(fabs(gora%2)==fabs(p[i].b%2)) p[i].maks = p[i].b;
			else p[i].maks = p[i].b - 1;//zakladajac zasieg ze dol tam wlatuje
		}
		else p[i].maks = gora;
    
		if(dol < p[i].a) {
			if(fabs(dol%2)==fabs(p[i].a%2)) p[i].mini = p[i].a;
			else p[i].mini = p[i].a + 1;//zakladajac zasieg ze gora tam wleci
		}
		else p[i].mini = dol; //mini i maks to wartosci wstrzelenia sie od poprzedniej przeszkody w te
		
		if(p[i].maks<p[i].a||p[i].mini>p[i].b) {
			cout<<"NIE";
			return 0;
		}
		p[i].k = p[i-1].k + ((d + p[i].mini-p[i-1].mini)/2);
	}
	cout<<p[n].k;
	return 0;
}
