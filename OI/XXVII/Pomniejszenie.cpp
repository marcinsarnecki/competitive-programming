#include<bits/stdc++.h>
#define N 100005
using namespace std;
int t, k, len, best, dif, rest;
string s1,s2;
int pref[N], A[N], B[N];
void solve()
{
	cin>>s1>>s2>>k;
	len = s1.size();
	best = dif = rest = 0;
	for(int i = 1; i <= len; i++) {
		A[i] = s1[i-1] - 48;
		B[i] = s2[i-1] - 48;
		pref[i] = pref[i-1] + (A[i]!=B[i]);
	}
	for(int i = 1; i <= len; i++) {
		dif = pref[i - 1], rest = len - i;
		if(A[i] >= B[i]) {
			if(k >= dif + 1 && k <= dif + 1 + rest && B[i] != 0) best = i;
		}
		if(A[i] < B[i]) {
			if(B[i] == 1) {
				if(k >= dif && k <= dif + rest) best = i;
			}
			if(B[i] > 1) {
				if(k >= dif && k <= dif + 1 + rest) best = i;
			}
		}
	}
	rest = len - best;
	if(best == 0) {
		cout<<"-1\n";
		return;
	}
	for(int i = 1; i < best; i++) {
		if(A[i] != B[i]) {	
			A[i] = B[i];
			k--;
		}
	}
	if(A[best] < B[best] && B[best] > 1 && k > 0) {
		if(A[best] != B[best] - 1) 
		{
			A[best] = B[best] - 1;
			k--;
		}
		else 
		{
			if(k > rest) {
				A[best] = B[best] - 2;
				k--;
			}	
		}
		
	}
	else if(A[best] >= B[best]) {
		A[best] = B[best] - 1;
		k--;
	}
	for(int i = best + 1; i <= len; i++) {
		if(A[i] < 9 && k > 0) {
			A[i] = 9;
			k--;
		}
		else if(A[i] == 9 && k == len - i + 1) {
			A[i] = 8;
			k--;
		}
	}
	for(int i = 1; i <= len; i++) cout<<A[i];
	cout<<"\n";
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>t;
	for(int i = 1; i <= t; i++) solve();
	return 0;
}
