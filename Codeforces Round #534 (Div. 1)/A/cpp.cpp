#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
string s;
int n;
bool b1 = 0, b2 = 0;
int main() {
	Hzy("A");
	cin >> s;
	n = s.size();
	for(int i = 0; i < n; ++i)
		if(s[i] == '0') {
			if(b1) {
				puts("3 1");
				b1 = 0;
			}
			else {
				puts("1 1");
				b1 = 1;
			}
		}
		else {
			if(b2) {
				puts("4 1");
				b2 = 0;
			}
			else {
				puts("4 3");
				b2 = 1;
			}
		}
	return 0;
}
