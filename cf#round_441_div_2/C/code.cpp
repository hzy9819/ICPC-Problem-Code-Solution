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

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, len;
int calc_bit(int x) {
	int ans(0);
	while(x) ans++, x /= 10;
	return ans;
}
int f(int x) {
	int ans(x);
	while(x) ans += x % 10, x /= 10;
	return ans;
}
int sz(0), ans[1010];

int main() {
	//Hzy("C");
	n = read();
	len = calc_bit(n);
	for(int i = max(1, n - 9 * len); i <= n; ++i)
		if(f(i) == n) ans[++sz] = i;
	printf("%d\n", sz);
	for(int i = 1; i <= sz; ++i) printf("%d\n", ans[i]);
	return 0;
}
