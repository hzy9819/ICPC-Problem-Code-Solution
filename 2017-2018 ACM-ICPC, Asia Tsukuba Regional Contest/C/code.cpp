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
const int N = 100010;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL s[N], a[N], m[N], n, t;

LL calc(int x, LL ans) { return s[x] - a[m[x]] + a[m[x]] * ans; }

int main() {
	Hzy("C");
	n = read(), t = read();
	int p = -1;
	for(int i = 1; i <= n; ++i) {
		a[i] = read(), s[i] = s[i - 1] + a[i];
		if(p == -1 || a[i] > a[p]) p = i;
		m[i] = p;
	}
	for(int i = 1; i <= n; ++i) {
		LL l = 1, r = 2e9;
		for(LL mid = (l + r) >> 1; l < r; mid = (l + r) >> 1)
			if(calc(i, mid) > t) r = mid;
			else l = mid + 1;
		printf("%lld\n", l);
	}
	return 0;
}
