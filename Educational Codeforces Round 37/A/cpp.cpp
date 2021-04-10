#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 210;
int t, n, k;
int a[N], ans;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int calc(int t) {
	if(t == 1) return 1;
	return t / 2 + 1;
}
int main() {
	Hzy("A");
	t = read();
	while(t--) {
		ans = 0;
		n = read(), k = read();
		for(int i = 1; i <= k; ++i) a[i] = read();
		ans = max(a[1], n - a[k] + 1);
		for(int i = 2; i <= k; ++i) ans = max(ans, calc(a[i] - a[i - 1]));
		printf("%d\n", ans);
	}
	return 0;
}
