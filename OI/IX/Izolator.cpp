#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> a(n);
    ll ans = 0;
    rep(i,0,n-1) {
        cin>>a[i];
        ans += a[i];
    }
    sort(a.begin(), a.end());
    for(int i = 0, j = n - 1; i < j; i++, j--)
        ans += a[j] - a[i];
    cout<<ans<<"\n";
    return 0;
}
