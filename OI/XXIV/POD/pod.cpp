#include<cstdio>
#define MAX_B 1000000
#define MAX_Q 100001
struct cyfra
{
	int i;
	long long l,p;	
};
cyfra P[MAX_B];
long long B[MAX_B];
long long Q[MAX_Q];
int s=0;
long long ostatnia;
int zapytanie(long long pozycja)
{
	if(pozycja>ostatnia) return -1;
	long long lewa_granica=0;
	long long prawa_granica=s-1;
	long long mid=(lewa_granica+prawa_granica)/2;
	while(!	(	P[mid].l<=pozycja && pozycja<=P[mid].p	)	)
	{
		if(	pozycja<P[mid].l	) prawa_granica=mid;
		else lewa_granica=mid+1;
		mid=(lewa_granica+prawa_granica)/2;
	}
	return P[mid].i;
}
int main()
{
	int b,q;
	long long suma_cyfr=0;
	scanf("%d%d",&b,&q);
	scanf("%d",&(B[0]));
	for(int i=1;i<b;++i)
		{
		 scanf("%lld",&(B[i]));
		 suma_cyfr=suma_cyfr+(B[i]*i);
		}
	for(int i=1;i<=q;++i) scanf("%lld",&(Q[i]));
	long long reszta=suma_cyfr%(b-1);
	if(reszta!=0) B[reszta]--;
	long long granica = 0;
	for(int i=0;i<b;++i)
		{
			if(B[i]>0)
				{
					P[s].i=i;
					P[s].l=granica;
					granica=granica+B[i]-1;
					P[s].p=granica;
					granica++;
					s++;
				}
		}
	ostatnia=P[s-1].p;
	for(int i=1;i<=q;++i)
		{
			printf("%d\n",zapytanie(Q[i]));
		}	
	return 0;
}
