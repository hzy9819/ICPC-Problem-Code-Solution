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
int T, n;
string s;
bool b;
int main() {
	Hzy("A");
	T = read();
	for(int i = 1; i <= T; ++i) {
		n = read();
		cin >> s;
		b = 1;
		for(int i = 0; i < (n / 2); ++i)
			if(abs(s[i] - s[n - 1 - i]) != 0 && abs(s[i] - s[n - 1 - i]) != 2)
				b = 0;
		if(b) puts("YES");
		else puts("NO");
	}
	return 0;
}
