#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
LL n, k, bin[110];
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("B");
	n = read(), k = read();
	bin[0] = 1;
	int sz; LL ans(0);
	for(sz = 1; ; ++sz) {
		bin[sz] = bin[sz - 1] << 1;
		if(bin[sz] > n) break;
	}
	if(k == 1) ans = n;
	else ans = bin[sz] - 1;
	printf("%lld\n", ans);
	return 0;
}
