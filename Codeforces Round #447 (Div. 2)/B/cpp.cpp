#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const LL weg = (1e+9) + 7;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, m, k;
LL mode_xp(LL a, LL b, LL p) {
	LL ans = 1;
	a %= p;
	while(b) {
		if(b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int main() {
	Hzy("B");
	n = read(), m = read(), k = read();
	if(((n + m) & 1LL) && (k == -1)) {
		puts("0");
		return 0;
	}
	printf("%I64d\n", mode_xp(mode_xp(2, n - 1, weg), m - 1, weg));
	return 0;
}
