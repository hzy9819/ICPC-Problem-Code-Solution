#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

LL read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL c1, c2, c3;
LL a1, a2, a3, a4, a5;

int main() {
	int T = read();
	while(T--) {
		c1 = read(), c2 = read(), c3 = read();
		a1 = read(), a2 = read(), a3 = read(), a4 = read(), a5 = read();
		c1 -= a1, c2 -= a2, c3 -= a3;
		if(c1 < 0 || c2 < 0 || c3 < 0) {
			puts("NO");
			continue;
		}
		a4 = max(0LL, a4 - c1);
		a5 = max(0LL, a5 - c2);
		c3 -= a4 + a5;
		if(c3 < 0)
			puts("NO");
		else
			puts("YES");
	}
	return 0;
}
