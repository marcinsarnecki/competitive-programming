#include<bits/stdc++.h>
using namespace std;
long long a, fib[100];
int p;

int podzial(long long k)
{
	if(k <= 3) return 1;//brzeg
	int ans = 0;
	int i = 2;
	while(!(fib[i] <= k && k < fib[i + 1])) i++;//wstepne nastawienie
	
	while(1)
	{
		if(fib[i] == k) return ++ans;
		if(k - fib[i] <= fib[i + 1] - k)//branie tej blizszej z pierwszej mniejszej/pierwszej wiekszej
		{
			k = k - fib[i];
			ans++;
		}
		else
		{
			k = fib[i + 1] - k;
			ans++;
		}
		while(fib[i] > k) i--;//k sie zmniejszylo wiec trzeba przesunac i 
	}
}
int main()
{
	ios_base::sync_with_stdio(0);
	fib[1] = fib[2] = 1;
	for(int i = 3; i <= 92; i++) fib[i] = fib[i - 2] + fib[i - 1];
	
	cin>>p;
	for(int i = 1; i <= p; i++)	{
		cin>>a;
		cout<<podzial(a)<<"\n";
	}
	
	return 0;
}
