#include<bits/stdc++.h>
using namespace std;

int n;
long long X,Y;//pytanie
long long px,py;//przesuniecie
int program[100001];
long long d, T;
long long currentx, currenty;
int dir;//0 1 2 3 gora prawo dol lewo
long long ans;
struct kraw
{
	long long x,y;
	int d;
}k[100001];
long long ilekolizji(long long l, long long r, long long mnoznik, long long p, long long x)
{
	long long kk;
	long long kkk;
	long long ans = 0;
	if(x < l)
	{
		x = r + (l - x);
		p *= -1;
	}
	if(x > r)
	{
		if(p < 0) return 0;
		if((x - r) % p == 0) kk = (x - r) / p;
		else kk = (x - r) / p + 1;
		l += kk * p;
		r += kk * p;
		mnoznik -= kk;
		if(mnoznik <= 0) return 0;
	}
	if(x >= l && x <= r)
	{
		long long d;
		if(p > 0) 
		{
			d = x - l;
			kk = d / p;
			if(mnoznik > kk) ans = kk + 1;
			else ans = mnoznik;
			return ans;
		}
		else
		{
			d = x - r;
			kk = d / p;
			if(mnoznik > kk) ans = kk + 1;
			else ans = mnoznik;
			return ans;
		}
	}
	if(x < l) return 0;
}

void ZaCyklem(long long Tleft)
{
	if(Tleft == 0 && X == currentx && Y == currenty) ans++;
	for(int i = 1; Tleft > 0; i++)	
		{
			if(dir == 0) //gora
			{
				if(program[i] == Tleft || program[i] + 1 == Tleft) 
				{
					if(X == currentx && Y >= currenty && Y <= currenty + program[i]) ans++;
					currenty += program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] < Tleft) 
				{
					if(X == currentx && Y >= currenty && Y < currenty + program[i]) ans++;
					currenty += program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] > Tleft) 
				{
					if(X == currentx && Y >= currenty && Y <= currenty + Tleft) ans++;
					Tleft = 0;
				}
			}
			if(dir == 1)
			{
				if(program[i] == Tleft || program[i] + 1 == Tleft)	
				{
					if(Y == currenty && X >= currentx && X <= currentx + program[i]) ans++;
					currentx += program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] < Tleft)	
				{
					if(Y == currenty && X >= currentx && X < currentx + program[i])	ans++;
					currentx += program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] > Tleft)	
				{
					if(Y == currenty && X >= currentx && X <= currentx + Tleft)	ans++;
					Tleft = 0;
				}
			}
			if(dir == 2)
			{
				if(program[i] == Tleft || program[i] + 1 == Tleft)	
				{
					if(X == currentx && Y <= currenty && Y >= currenty - program[i]) ans++;
					currenty -= program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] < Tleft)	
				{
					if(X == currentx && Y <= currenty && Y > currenty - program[i])	ans++;
					currenty -= program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] > Tleft)	
				{
					if(X == currentx && Y <= currenty && Y >= currenty - Tleft)	ans++;
					Tleft = 0;
				}
			}
			if(dir == 3)
			{
				if(program[i] == Tleft || program[i] + 1 == Tleft)	
				{
					if(Y == currenty && X <= currentx && X >= currentx - program[i]) ans++;
					currentx -= program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] < Tleft)	
				{
					if(Y == currenty && X <= currentx && X > currentx - program[i])	ans++;
					currentx -= program[i];
					Tleft -= program[i] + 1;
				}
				else if(program[i] > Tleft)	
				{
					if(Y == currenty && X <= currentx && X >= currentx - Tleft)	ans++;
					Tleft = 0;
				}
			}
			dir = (dir + 1) % 4;
			if(i == n) i = 0;
		}
}

int main()
{
	ios_base::sync_with_stdio(0);
	
	cin>>n>>T;
	for(int i = 1; i <= n; i++) cin>>program[i];
	cin>>X>>Y;
	
	for(int i = 1; i <= n; i++) 
	{
		k[i].x = currentx;
		k[i].y = currenty;
		k[i].d = program[i];
		if(dir == 0) currenty += program[i];
		if(dir == 1) currentx += program[i];
		if(dir == 2) currenty -= program[i];
		if(dir == 3) currentx -= program[i];
		dir = (dir + 1) % 4;
		d += program[i] + 1;//+1 bo skret w prawo	
	}
	px = currentx;
	py = currenty;
	currentx = currenty = dir = 0;
	if(n % 4 == 1 || n % 4 == 3 || ( n % 2 == 0 && n % 4 != 0 ) || (n % 4 == 0 && (px == 0 && py == 0)))
	{
		long long mnoznik = T / (d * 4);
		long long Tleft = T - (mnoznik * (d * 4));
		if(mnoznik > 0)
		{
			currentx = currenty = dir = 0;
			long long kolizje = 0;
			for(int j = 1; j <= 4; j++)
				for(int i = 1; i <= n; i++)
				{
					if(dir == 0) 
					{
						if(X == currentx && Y >= currenty && Y < currenty + program[i]) kolizje++;
						currenty += program[i];
					}
					if(dir == 1) 
					{
						if(Y == currenty && X >= currentx && X < currentx + program[i]) kolizje++;
						currentx += program[i];
					}
					if(dir == 2) 
					{
						if(X == currentx && Y <= currenty && Y > currenty - program[i]) kolizje++;
						currenty -= program[i];
					}
					if(dir == 3) 
					{
						if(Y == currenty && X <= currentx && X > currentx - program[i]) kolizje++;
						currentx -= program[i];
					}
					dir = (dir + 1) % 4;
				}
			ans += mnoznik * kolizje;
		}
		ZaCyklem(Tleft);
		cout<<ans;
	}
	else	
	{
		if(px == 0)
		{
			long long mnoznik = T / d;
			long long Tleft = T - (mnoznik * d);
			for(int i = 1; i <= n; i++)
			{
				if((i - 1) % 4 == 0)
				{
					if(X == k[i].x)	ans += ilekolizji(k[i].y, k[i].y + k[i].d, mnoznik, py, Y);
					
				}
				if((i - 1) % 4 == 1)
				{
					long long l = k[i].x, r = k[i].x + k[i].d;
					if(X > l && X < r)
					{
						long long d = Y - k[i].y;
						if(d % py == 0)
						{
							long long kk = d / py;
							if(kk >= 0 && mnoznik > kk) ans++;
						}	
					}
				}
				if((i - 1) % 4 == 2)
				{
					if(X == k[i].x)	ans += ilekolizji(k[i].y - k[i].d, k[i].y, mnoznik, py, Y);
				}
				if((i - 1) % 4 == 3)
				{
					long long l = k[i].x - k[i].d, r = k[i].x;
					if(X > l && X < r)
					{
						long long d = Y - k[i].y;
						if(d % py == 0)
						{
							long long kk = d / py;
							if(kk >= 0 && mnoznik > kk) ans++;	
						}	
					}
				}	
			}
			currentx = px * mnoznik;
			currenty = py * mnoznik;
			ZaCyklem(Tleft);
			cout<<ans;
		}
		else if(py == 0)
		{
			long long mnoznik = T / d;
			long long Tleft = T - (mnoznik * d);
			if(X == 0 && Y == 0 && mnoznik > 0) ans++;
			for(int i = 1; i <= n; i++)
			{
				if((i - 1) % 4 == 0)
				{
					long long l = k[i].y, r = k[i].y + k[i].d;
					if(Y > l && Y < r)
					{
						long long d = X - k[i].x;
						if(d % px == 0)
						{
							long long kk = d / px;
							if(kk >= 0 && mnoznik > kk) ans++;
						}
					}
				}
				if((i - 1) % 4 == 1)
				{
					if(Y == k[i].y)
					{
						ans += ilekolizji(k[i].x, k[i].x + k[i].d, mnoznik, px, X);
					}
				}
				if((i - 1) % 4 == 2)
				{
					long long l = k[i].y, r = k[i].y - k[i].d;
					if(Y < l && Y > r)
					{
						long long d = X - k[i].x;
						if(d % px == 0)
						{
							long long kk = d / px;
							if(kk >= 0 && mnoznik > kk) ans++;
						}
						
					}
				}
				if((i - 1) % 4 == 3)
				{
					if(Y == k[i].y)	ans += ilekolizji(k[i].x - k[i].d, k[i].x, mnoznik, px, X);//serio czytasz to? xD
				}	
			}
			currentx = px * mnoznik;
			currenty = py * mnoznik;
			if(currenty == Y && currentx == X && mnoznik > 0) ans--;
			ZaCyklem(Tleft);
			cout<<ans;
		}
		else
		{
			long long mnoznik = T / d;
			long long Tleft = T - (mnoznik * d);	
			if(mnoznik > 0)
			{
				currentx = currenty = dir = 0;
				long long kolizje = 0;
				for(int i = 1; i <= n; i++)
				{
					if((i - 1) % 4 == 0)
					{
						if((X - k[i].x) % px == 0 || X - k[i].x == 0)
						{
							long long kkk = (X - k[i].x) / px;
							currentx = k[i].x + kkk * px;
							currenty = k[i].y + kkk * py;
							if(kkk >= 0 && kkk < mnoznik) if(Y >= currenty && Y < currenty + k[i].d) ans++;
						}
					}
					if((i - 1) % 4 == 1)
					{
						if((Y - k[i].y) % py == 0 || Y - k[i].y == 0)
						{
							long long kkk = (Y - k[i].y) / py;
							currentx = k[i].x + kkk * px;
							currenty = k[i].y + kkk * py;
							if(kkk >= 0 && kkk < mnoznik) if(X >= currentx && X < currentx + k[i].d) ans++;
						}
					}
					if((i - 1) % 4 == 2)
					{
						if((X - k[i].x) % px == 0 || X - k[i].x == 0)
						{
							long long kkk = (X - k[i].x) / px;
							currentx = k[i].x + kkk * px;
							currenty = k[i].y + kkk * py;
							if(kkk >= 0 && kkk < mnoznik) if(Y <= currenty && Y > currenty - k[i].d) ans++;
						}
					}
					if((i - 1) % 4 == 3)
					{
						if((Y - k[i].y) % py == 0 || Y - k[i].y == 0)
						{
							long long kkk = (Y - k[i].y) / py;
							currentx = k[i].x + kkk * px;
							currenty = k[i].y + kkk * py;
							if(kkk >= 0 && kkk < mnoznik) if(X <= currentx && X > currentx - k[i].d) ans++;	
						}
					}
				}
				
				
			}
			currentx = px * mnoznik;
			currenty = py * mnoznik;
			ZaCyklem(Tleft);
			cout<<ans;	
		}	
	}
	return 0;
}
