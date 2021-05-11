#include<bits/stdc++.h>
using namespace std;
#define N 1000001
int rightA[N][2], rightC[N][2], rightG[N][2], rightT[N][2];
int leftA[N][2], leftC[N][2], leftG[N][2], leftT[N][2]; 
string s1, s2;
int lastA, lastC, lastG, lastT;

struct litera
{
	int l1,l2,p1,p2;
	char z;	
	litera(int a, int b, int c, int d, char e)
	{
		l1 = a;
		p1 = b;
		l2 = c;
		p2 = d;
		z = e;
	}
};
list<litera> l;

int func(int a1, int b1, int a2, int b2)
{
	if(a1 > s1.size() || a2 > s2.size()) return 0;
	if(rightA[a1][0] <= b1 && rightA[a2][1] <= b2) return 1;//A
	if(rightC[a1][0] <= b1 && rightC[a2][1] <= b2) return 2;//C
	if(rightG[a1][0] <= b1 && rightG[a2][1] <= b2) return 3;//G
	if(rightT[a1][0] <= b1 && rightT[a2][1] <= b2) return 4;//T
	return 0;
}

void aktualizuj(list<litera>::iterator it,int l1,int l2)
{
	if((*it).z == 'A'){
		(*it).l1 = rightA[l1][0];
		(*it).l2 = rightA[l2][1];
	}
	if((*it).z == 'C'){
		(*it).l1 = rightC[l1][0];
		(*it).l2 = rightC[l2][1];
	}
	if((*it).z == 'G'){
		(*it).l1 = rightG[l1][0];
		(*it).l2 = rightG[l2][1];
	}
	if((*it).z == 'T'){
		(*it).l1 = rightT[l1][0];
		(*it).l2 = rightT[l2][1];
	}
}

void popraw()
{
	litera wartownik1 = litera(0, 0, 0, 0, 'X');
	litera wartownik2 = litera(N, s1.size() + 1, N, s2.size() + 1, 'X'); 
	l.push_back(wartownik1);
	l.push_back(wartownik2);
	for(list<litera>::iterator it = l.begin(); it != --l.end();)
	{
		if(it != l.begin() && (*it).z == 'X') break;
		int l1 = (*it).l1, l2 = (*it).l2;
		list<litera>::iterator it2 = it;
		it2++;
		int p1 = (*it2).p1, p2 = (*it2).p2;
		int id = func(l1 + 1,p1 - 1,l2 + 1,p2 - 1);
		if(id == 1){
			l1 = rightA[l1 + 1][0];
			l2 = rightA[l2 + 1][1];
			p1 = leftA[p1 - 1][0];
			p2 = leftA[p2 - 1][1];
			l.insert(it2,litera(l1,p1,l2,p2,'A'));
			aktualizuj(it2,l1 + 1,l2 + 1);
		}
		if(id == 2){
			l1 = rightC[l1 + 1][0];
			l2 = rightC[l2 + 1][1];
			p1 = leftC[p1 - 1][0];
			p2 = leftC[p2 - 1][1];
			l.insert(it2,litera(l1,p1,l2,p2,'C'));
			aktualizuj(it2,l1 + 1,l2 + 1);
		}
		if(id == 3){
			l1 = rightG[l1 + 1][0];
			l2 = rightG[l2 + 1][1];
			p1 = leftG[p1 - 1][0];
			p2 = leftG[p2 - 1][1];
			l.insert(it2,litera(l1,p1,l2,p2,'G'));
			aktualizuj(it2,l1 + 1,l2 + 1);
		}
		if(id == 4){
			l1 = rightT[l1 + 1][0];
			l2 = rightT[l2 + 1][1];
			p1 = leftT[p1 - 1][0];
			p2 = leftT[p2 - 1][1];
			l.insert(it2,litera(l1,p1,l2,p2,'T'));
			aktualizuj(it2,l1 + 1,l2 + 1);
		}
		if(id == 0){
			it++;//??
			aktualizuj(it2,l1 + 1,l2 + 1);
		}
	}	
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin>>s1>>s2;
	lastA = lastC = lastG = lastT = N;
	for(int i = s1.size() - 1; i >= 0; i--){
		if(s1[i] == 'A') lastA = i + 1;
		if(s1[i] == 'C') lastC = i + 1;
		if(s1[i] == 'G') lastG = i + 1;
		if(s1[i] == 'T') lastT = i + 1;
		rightA[i + 1][0] = lastA;
		rightC[i + 1][0] = lastC;
		rightG[i + 1][0] = lastG;
		rightT[i + 1][0] = lastT;
	}
	lastA = lastC = lastG = lastT = N;
	for(int i = s2.size() - 1; i >= 0; i--){
		if(s2[i] == 'A') lastA = i + 1;
		if(s2[i] == 'C') lastC = i + 1;
		if(s2[i] == 'G') lastG = i + 1;
		if(s2[i] == 'T') lastT = i + 1;
		rightA[i + 1][1] = lastA;
		rightC[i + 1][1] = lastC;
		rightG[i + 1][1] = lastG;
		rightT[i + 1][1] = lastT;
	}
	lastA = lastC = lastG = lastT = 0;
	for(int i = 0; i < s1.size(); i++)
	{
		if(s1[i] == 'A') lastA = i + 1;
		if(s1[i] == 'C') lastC = i + 1;
		if(s1[i] == 'G') lastG = i + 1;
		if(s1[i] == 'T') lastT = i + 1;
		leftA[i + 1][0] = lastA;
		leftC[i + 1][0] = lastC;
		leftG[i + 1][0] = lastG;
		leftT[i + 1][0] = lastT;
	}
	lastA = lastC = lastG = lastT = 0;
	for(int i = 0; i < s2.size(); i++)
	{
		if(s2[i] == 'A') lastA = i + 1;
		if(s2[i] == 'C') lastC = i + 1;
		if(s2[i] == 'G') lastG = i + 1;
		if(s2[i] == 'T') lastT = i + 1;
		leftA[i + 1][1] = lastA;
		leftC[i + 1][1] = lastC;
		leftG[i + 1][1] = lastG;
		leftT[i + 1][1] = lastT;
	}
	popraw();
	for(list<litera>::iterator it = ++l.begin(); it != --l.end(); it++)
		cout<<(*it).z;
	return 0;
}
