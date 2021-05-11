#include<bits/stdc++.h>
using namespace std;
int n,m,kon[100001],odw[100001],l,p,mid;

bool proboj(int k)
{
//	cout<<"k="<<k<<"\n";
	priority_queue<int> pq;
	for(int i = 1; i <= n; i++) pq.push(kon[i]);
	for(int i = k; i >= 1; i--)
	{
		int x = odw[i];
		if(!pq.empty() && pq.top()>=x)
		{
			int y = pq.top();
			pq.pop();
			y -= x;
			if(y) pq.push(y);
		}
		else return false;
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin>>n>>m;
	for(int i = 1; i <= n; i++) cin>>kon[i];
	for(int i = 1; i <= m; i++) cin>>odw[i];
//	sort(kon+1,kon+1+n);
	sort(odw+1,odw+1+m);
	l = 0;
	p = m;
	mid = (l + p) / 2;
	while(l <= p)
	{
//		cout<<l<<" "<<p<<"\n";
		if(proboj(mid)) l = mid + 1;
		else p = mid - 1;
		mid = (l + p) / 2;
	}
	cout<<l - 1;
	return 0;
}
