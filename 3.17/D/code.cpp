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
const int N = 15;
const int K = 100;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

db FM(db k, LL b) {
	db ans = 1.00;
	while(b) {
		if(b & 1) ans = ans * k;
		k = k * k;
		b >>= 1;
	}
	return ans;
}
db f[N][K], g[N][K];
db p[N], ans[N];
LL s[N];
int main() {
	Hzy("D");
	int t = read(), n;
	while(t--) {
		n = read();
		for(int i = 1; i <= n; ++i)
			s[i] = read(), scanf("%lf", p + i);
		if(n == 1) {
			puts("1.000000");
			continue;
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < K; ++j) {
				f[i][j] = FM(1 - FM(p[i], j), s[i]);
				g[i][j] = 1.0 - f[i][j];
			}
		for(int i = 1; i <= n; ++i) {
			ans[i] = 0.000000;
			for(int j = 1; j < K - 1; ++j) {				
				db tmp = g[i][j] - g[i][j + 1];
				for(int k = 1; k <= n; ++k) {
					if(k == i) continue;
					//db tmp = g[i][j] - g[i][j + 1];
					//ans[i] += tmp * f[k][j - 1];
					tmp *= f[k][j];
				}
				ans[i] += tmp;
			}
		}
		for(int i = 1; i < n; ++i)
			printf("%.6lf ", ans[i]);
		printf("%.6lf", ans[n]);
		puts("");
	}
	return 0;
}
