#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const ll INF = 1000000000000000000ll;

#define N 100

ll n, k;
vector<int> bity;
bool tab[N][N];

int main() {
	ios_base::sync_with_stdio(0);
	cin>>k;
	if(k == 0) {
		cout<<"1\n";
		cout<<"#\n";
		return 0;
	}
	if(k <= 15) {
		n = k;
		cout<<n<<"\n";
		rep(i,1,n-1) {
			cout<<"..";
			rep(j,1,n-2)
				cout<<"#";
			cout<<"\n";
		}
		rep(j,1,n)
			cout<<".";
		cout<<"\n";
		return 0;
	}
	while(k > 0) {
		int num = (k&2) + (k&1);
		bity.pb(num);
		k >>= 2; 
	}
	reverse(bity.begin(), bity.end());
	int row = 3, column = 4;
	rep(i,1,3)						
		tab[1][i] = tab[i][4] = 1;	
	if(bity[0] == 2)				
		tab[2][3] = 1;				
	if(bity[0] == 3)				
		tab[3][3] = tab[2][3] = 1;	
	bity.erase(bity.begin());
	for(int b: bity) {
		rep(i,0,3)
			rep(j,0,1)
				tab[row + i][column + j] = 1;
		row += 3;
		column += 1;
		if(b == 1)
			rep(j,1,column)
				tab[row][j] = 1;
		if(b == 2) 
			rep(j,1,column)
				tab[row-1][j] = 1;
		if(b == 3) {
			rep(j,1,column)
				tab[row-1][j] = 1;
			tab[row][column-2] = 1;
		}
	}
	n = row;
	rep(i,1,n)
		tab[i][1] = 1;
	rep(j,column,n)
		tab[n][j] = 1;
	cout<<n<<"\n";
	rep(i,1,n) {
		rep(j,1,n)
			if(tab[i][j])
				cout<<".";
			else
				cout<<"#";
		cout<<"\n";
	}
	return 0;
}
