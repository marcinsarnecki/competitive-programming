#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 1001
int n, m, rows[N], columns[N], ans;

int main() {
	ios_base::sync_with_stdio(0);
	cin>>m>>n;
	rep(i,1,m-1)
		cin>>columns[i];
	rep(i,1,n-1)
		cin>>rows[i];
	sort(columns + 1, columns + m);
	sort(rows + 1, rows + n);
	int j = m - 1, i = n - 1;
	while(i >= 1 || j >= 1) 
		if(rows[i] > columns[j]) 
			ans += rows[i--] * (m - j);
		else
			ans += columns[j--] * (n - i);
	cout<<ans<<"\n";
	return 0;
}
