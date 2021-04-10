#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL gcd(LL a, LL b) {
	if(a < b)
		swap(a, b);
	LL c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

LL n, m, q;

int main() {
	n = read(), m = read(), q = read();
	LL d = gcd(n, m);
	LL nn = n / d, mm = m / d;
	LL sx, sy, ex, ey;
	for(int i = 1; i <= q; ++i) {
		sx = read(), sy = read(), ex = read(), ey = read();
		(sy - 1) / (sx == 1 ? nn : mm) == (ey - 1) / (ex == 1 ? nn : mm) ? puts("YES") : puts("NO");
	}
	
	return 0;
}
