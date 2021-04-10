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
const int N = 1010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, ans;
int s[N], d[N];

int calc(int t, int p) {
	if(t < s[p]) return s[p];
	else if(t == s[p]) return s[p] + d[p];
	int tmp = (t - s[p]) / d[p];
	return s[p] + (tmp + 1) * d[p];
}

int main() {
	Hzy("A");
	n = read();
	for(int i = 1; i <= n; ++i) s[i] = read(), d[i] = read();
	ans = 0;
	for(int i = 1; i <= n; ++i) ans = calc(ans, i);
	printf("%d\n", ans);
	return 0;
}
