#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1000010;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Seg {
	LL l, r;
}a[N];
bool cmp(const Seg & x, const Seg & y) { return x.l < y.l;}
LL n, d, re = 0;
int main() {
	Hzy("B");
	n = read(), d = n;
	LL l, r, t;
	for(int i = 1, cnt = 1; i <= n; ++i, cnt++) {
		t = read();
		if(!t) {i--, n--;continue;}
		l = cnt - t, r = cnt - 1;
		l = max(l, 0LL);
		a[i].l = l, a[i].r = r;
	}
	sort(a + 1, a + n + 1, cmp);
	LL pre = 0;
	for(int i = 1; i <= n; ++i) if(a[i].l > pre) re += a[i].l - pre - 1, pre = a[i].r;
		else pre = max(pre, a[i].r);
	re += d - pre;
	printf("%I64d", re);
	return 0;
}
