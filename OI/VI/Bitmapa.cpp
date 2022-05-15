#include<bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

#define N 200
bool tab[N][N], visited[N][N];
int ans[N][N];

int dy[]{-1, 0, 1, 0};
int dx[]{0, 1, 0, -1};

int main() {
    int n, m;
    cin>>n>>m;
    queue<pii> Q;
    rep(i,1,n) {
        string s;
        cin>>s;
        rep(j,1,m) {
            if(s[j-1] == '1') {
                tab[i][j] = 1;
                Q.push({i,j});
                visited[i][j] = 1;
            }
        }
    }
    rep(i,0,n+1)
        visited[i][0] = visited[i][m+1] = 1;
    rep(j,0,m+1)
        visited[0][j] = visited[n+1][j] = 1;
    while(Q.size() > 0) {
        pii v = Q.front();
        Q.pop();
        rep(i,0,3) {
            pii u = {v.f + dy[i], v.s + dx[i]};
            if(!visited[u.f][u.s]) {
                visited[u.f][u.s] = 1;
                ans[u.f][u.s] = ans[v.f][v.s] + 1;
                Q.push(u);
            }
        }
    }
    rep(i,1,n) {
        rep(j,1,m)
            cout<<ans[i][j]<<" ";
        cout<<"\n";
    }
}
