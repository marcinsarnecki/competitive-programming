#include<bits/stdc++.h>//prostokaty niskie i dluuuugie, to dziala
using namespace std;
int tab[250005], n, ans, useless;
stack<int> s;
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n;
	for(int i = 1; i <= n; i++) {
		cin>>useless>>tab[i];
	}
	s.push(-1);
	for(int i = 1; i <= n; i++){
		while(s.top() > tab[i]) s.pop();
		if(s.top() != tab[i]){
			ans++;
			s.push(tab[i]);
		}
	}
	cout<<ans;
	return 0;
}
