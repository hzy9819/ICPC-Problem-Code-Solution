#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int b, p, f, h, c;

int main() {
	int T = read() ;
	while(T--) {
		b = read(), p = read(), f = read();
		h = read(), c = read();
		if(b >= (p + f) * 2)
			printf("%d\n", p * h + f * c);
		else if(h > c)
			printf("%d\n", min(p, b / 2) * h + max(0, (b - 2 * p) / 2) * c);
		else
			printf("%d\n", min(f, b / 2) * c + max(0, (b - 2 * f) / 2) * h);
	}
	return 0;
}
