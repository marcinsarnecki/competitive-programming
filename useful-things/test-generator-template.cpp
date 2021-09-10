#include<bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define repv(i,a,b) for(int i = a; i >= b; i--)
using namespace std;

int losuj(int a, int b) {
	return rand()%(b - a + 1) + a;
}

int main(int argc, char** argv) {
	srand(atoi(argv[1]));
  
	return 0;
}
