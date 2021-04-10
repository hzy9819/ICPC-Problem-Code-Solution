#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
const int R = 60010;
const int INF = 1 << 30;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int f[N][R], a[N], b[N], ans = 0;

int n, r;

int main() {
	n = read(), r = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read(), b[i] = read();
		if(b[i] < 0)
			a[i] = max(a[i], abs(b[i]));
	}
	int lm = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = i + 1; j <= n; ++j)
			if(b[j] > b[i]) swap(a[i], a[j]), swap(b[i], b[j]);
		if(b[i] >= 0)
			lm = i;
	}
	for(int i = 1; i <= lm; ++i)
		for(int j = i + 1; j <= lm; ++j)
			if(a[j] < a[i]) swap(a[j], a[i]), swap(b[j], b[i]);
	for(int i = lm + 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
			if(a[j] + b[j] > a[i] + b[i]) swap(a[j], a[i]), swap(b[j], b[i]);
	for(int i = 0; i < R; ++i)
		f[0][i] = (i <= r ? 0 : -INF);
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < R; ++j) {
			f[i][j] = f[i - 1][j];
			if(j - b[i] >= a[i] && j - b[i] >= 0 && j - b[i] < R)
				f[i][j] = max(f[i][j], f[i - 1][j - b[i]] + 1);
			ans = max(ans, f[i][j]);
		}
	(ans == n) ? puts("YES") : puts("NO");
	return 0;
}
