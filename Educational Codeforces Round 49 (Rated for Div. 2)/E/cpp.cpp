#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const LL weg = 998244353;
const int N = 510;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL f[2][N][N], ans, n, K;
LL sum[N], s[N];
void add(LL & a, LL b) {
	a += b;
	if(a >= weg) a -= weg;
}
int main() {
	Hzy("E");
	n = read(), K = read() - 1;
	//if(K < n) return puts("0"), 0;
	int cur = 0;
	f[0][0][0] = 1;
	for(int i = 0; i < n; ++i) {
		cur ^= 1;
		memset(f[cur], 0, sizeof f[cur]);
		for(int j = 0; j <= n; ++j)
			for(int k = 0; k <= n; ++k) {
				add(f[cur][j + 1][max(j + 1, k)], f[cur ^ 1][j][k]);
				add(f[cur][1][max(k, 1)], f[cur ^ 1][j][k]);
			}
	}

	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			add(sum[i], f[cur][j][i]);

	for(int i = 0; i <= n; ++i) {
		add(s[i + 1], s[i]);
		add(s[i + 1], sum[i]);
	}

	for(int i = 1; i <= n; ++i)
		add(ans, sum[i] * s[min(n + 1, K / i + 1)] % weg);

	ans = (ans * ((weg + 1) / 2)) % weg;

	cout << ans << endl;
		
}
