#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;
const int C = 10010;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, w, b, x, cur;
LL c[N], cs[N];
LL f[2][C];
int q[C], sz, hd;
int main() {
	Hzy("E");
	n = read(), w = read(), b = read(), x = read();
	cur = 0;
	for(int i = 1; i <= n; ++i) c[i] = read();
	for(int i = 1; i <= n; ++i) cs[i] = read();
	memset(f, -1, sizeof f);
	f[cur][0] = w;
	int sum = c[1];
	for(int i = 1; i <= n; ++i) {
		cur ^= 1;
		sz = 0, hd = 1;
		//for(int j = 0; j <= sum; ++j) f[cur][j] = -1;
		for(int j = 0; j <= sum; ++j) {
			if(f[cur ^ 1][j] >= 0) {
				while(sz >= hd && f[cur ^ 1][j] >= (f[cur ^ 1][q[sz]] - cs[i] * (j - q[sz]))) sz--;
				q[++sz] = j;
			}
			if(hd <= sz && j - q[hd] > c[i]) hd++;
			if(hd <= sz) f[cur][j] = f[cur ^ 1][q[hd]] - cs[i] * (j - q[hd]);
			if(f[cur][j] >= 0) f[cur][j] = min(f[cur][j] + x, w + b * j);
		}
		sum += c[i + 1];
	}
	for(int i = sum; i >= 0; --i)
		if(f[cur][i] >= 0) {
			printf("%d\n", i);
			break ;
		}			
	return 0;
}
