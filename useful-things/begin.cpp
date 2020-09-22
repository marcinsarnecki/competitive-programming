//
//			Usage: compile this program and then run it in terminal ./begin newfile.cpp
//
#include<bits/stdc++.h>
using namespace std;
int main(int argc, char** argv) {
	if(argc == 1)
		return 0;
	string file  = argv[1];
	fstream plik;
	plik.open(file, ios::out);
	plik<<"#include<bits/stdc++.h>\n";
	plik<<"#define f first\n";
	plik<<"#define s second\n";
	plik<<"#define pb push_back\n";
	plik<<"#define rep(i,a,b) for(int i = a; i <= b; i++)\n";
	plik<<"#define repv(i,a,b) for(int i = a; i >= b; i--)\n";
	plik<<"using namespace std;\n";
	plik<<"typedef pair<int,int> pii;\n";
	plik<<"typedef long long ll;\n";
	plik<<"const long long INF = 1000000000000000000ll;\n\n\n\n";
	plik<<"int main() {\n";
	plik<<"	ios_base::sync_with_stdio(0);\n\n\n";
	plik<<"	return 0;\n";
	plik<<"}\n";
	plik.close();
	//string q = "geany " + file;
	//system(q.c_str());
	return 0;
}
