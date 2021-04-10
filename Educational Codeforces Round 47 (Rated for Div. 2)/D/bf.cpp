#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int n, m;
int gcd(int a, int b) {
	int c;
	if(b > a) swap(a, b);
	while(b)
		c = a % b, a = b, b = c;
	return a;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
pair <int, int> ans[N];
int sz;
int main() {
	Hzy("D");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
			if(gcd(i, j) == 1) {
				ans[++sz] = make_pair(i, j);
				if(sz >= m) break;
			}
	if(sz >= m) {
		puts("Possible");
		for(int i = 1; i <= m; ++i)
			printf("%d %d\n", ans[i].first, ans[i].second);
	}
	else
		puts("Impossible");
	return 0;
}
