//
//			Usage: compile this program and run it in terminal ./begin_gene gene.cpp
//			Its start for a program that generates tests
#include<bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
	if(argc == 1)
		return 0;
	string file  = argv[1];
	fstream plik;
	plik.open(file, ios::out);
	plik<<"#include<bits/stdc++.h>\n";
	plik<<"#define rep(i,a,b) for(int i = a; i <= b; i++)\n";
	plik<<"#define repv(i,a,b) for(int i = a; i >= b; i--)\n";
	plik<<"using namespace std;\n\n";
	plik<<"int losuj(int a, int b) {\n";
	plik<<"	return rand()%(b - a + 1) + a;\n";
	plik<<"}\n\n";
	plik<<"int main(int argc, char** argv) {\n";
	plik<<"	srand(atoi(argv[1]));\n\n\n";
	plik<<"	return 0;\n";
	plik<<"}\n";
	plik.close();
	return 0;
}
