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
LL n, m, x, d, t;
db ans, tmp;
int main() {
	Hzy("C");
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		x = read(), d = read();
		ans += x;
		if(d > 0) ans += (db) d * (n - 1) / 2;
		else t += d;
	}
	if(n & 1) ans += (db) t * (n * n - 1) / (4 * n);
	else ans += (db) n * t / 4;
	printf("%lf", ans);
	return 0;
}
