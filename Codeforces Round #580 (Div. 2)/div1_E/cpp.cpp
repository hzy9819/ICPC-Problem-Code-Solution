#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
const int weg = 1e9 + 7;

int n, k, p[N], mu[N], pw[N], tmp[N], vis[N], sz = 0, ans = 0;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void getMu() {
	mu[1] = 1;
	for(int i = 2; i < N; ++i) {
		if(!vis[i])
			p[++sz] = i, mu[i] = -1;
		for(int j = 1; j <= sz && i * p[j] < N; ++j) {
			vis[i * p[j]] = 1;
			if(i % p[j] == 0)
				break;
			mu[i * p[j]] = -mu[i];
		}
	}
}

int qpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1)
			res = 1LL * res * a % weg;
		a = 1LL * a * a % weg;
		n >>= 1;
	}
	return res;
}

int main() {
	n = read(), k = read();
	getMu();
	pw[0] = 1;
	for(int i = 1; i <= n; ++i)
		pw[i] = 1LL * pw[i - 1] * k % weg;
	for(int i = 1; i <= n - 1; ++i) {
		int m = 2 * (n - 1) / i;
		for(int t = 1; t <= m; ++t)
			for(int j = t; j <= m; j += t)
				tmp[j] += mu[t] * (min(j - 1, (n - 1) / i) / t - max(0, (i * j - n) / i) / t);

		for(int j = 1; j <= m; ++j)
			ans = (ans + 1LL * pw[max(i * j - n, i)] * tmp[j] % weg) % weg;
		for(int j = 0; j <= m; ++j)
			tmp[j] = 0;
	}
	ans = 1LL * ans * qpow(pw[n], weg - 2) % weg;
	cout << ans << endl;
	return 0;
}
