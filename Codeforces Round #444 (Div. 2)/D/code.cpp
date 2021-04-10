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
const int N = 300010;
struct Eve {
	int t, typ;
}e[N];
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, a, b, c, d, st, len, s[N];
int q[N], l, r;
int main() {
	Hzy("D");
	n = read(), a = read(), b = read(), c = read(), d = read(), st = read(), len = read();
	for(int i = 1; i <= n; ++i) {
		e[i].t = read(), e[i].typ = read();
		if(e[i].typ == 0) s[i] = s[i - 1] - d;
		else s[i] = s[i - 1] + c;
	}
	int t = 0;
	e[0].t = -1;
	for(int i = 1; i <= n; ++i) {
		while(t < n && e[t + 1].t - e[i - 1].t - 1 < len) {
			t++;
			while(l <= r && s[q[r]] >= s[t]) r--;
			q[++r] = t;
		}
		if(st + s[q[l]] - s[i - 1] >= 0) {
			printf("%d\n", e[i - 1].t + 1);
			return 0;
		}
		if(e[i].typ) st += a;
		else st -= b;
		if(l >= q[l]) l++;
		if(st < 0) break;
	}
	if(st >= 0) printf("%d\n", e[n].t + 1);
	else puts("-1");
	return 0;
}
