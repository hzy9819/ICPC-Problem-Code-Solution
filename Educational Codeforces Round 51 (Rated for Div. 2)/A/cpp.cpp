#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
char cg[10];
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

bool check(string s) {
	bool f1 = 0, f2 = 0, f3 = 0;
	for(int i = 0; i < s.size(); ++i) {
		if((s[i] >= 'a' && s[i] <= 'z')) f1 = 1;
		if((s[i] >= 'A' && s[i] <= 'Z')) f2 = 1;
		if((s[i] >= '0' && s[i] <= '9')) f3 = 1;
	}
	return (f1 && f2 && f3);
}
string work(string s) {
	if(check(s)) return s;
	for(int i = 1; i <= 3; ++i)
		for(int j = 0; j + i - 1 < s.size(); ++j) {
			string tmp = s;
			for(int k = 1; k <= i; ++k)
				tmp[j + k - 1] = cg[k];
			if(check(tmp)) return tmp;
			for(int k = 1; k <= i; ++k)
				tmp[j + k - 1] = cg[k + 1];
			if(check(tmp)) return tmp;
			for(int k = 1; k <= i; ++k)
				tmp[j + k - 1] = cg[k + 2];
			if(check(tmp)) return tmp;
		}
	return s;
}

int main() {
	Hzy("A");
	int T = read();
	cg[1] = cg[4] = '0';
	cg[2] = cg[5] = 'a';
	cg[3] = 'A';
	while(T--) {
		string s;
		cin >> s;
		cout << work(s) << endl;
	}
	return 0;
}
