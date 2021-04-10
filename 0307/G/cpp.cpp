#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N1 = 370;
const int N2 = 36510;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, N, c[N1];
db fac[N2], ans;
int ct[N1], cnt = 0;

db C(int n, int m) { return fac[n] - fac[m] - fac[n - m]; }

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		c[i] = read();
		N += c[i];
	}
	sort(c + 1, c + n + 1);
	for(int i = 1; i <= n; ++i)
		if(c[i] != c[i - 1])
			ct[ ++cnt] = 1;
		else
			ct[cnt]++;
	fac[0] = 0;
	for(int i = 1; i <= max(365, N); ++i)
		fac[i] = fac[i - 1] + log10( (db) i);
	db num = log10(365);
	db ans = C(365, n);
	int tmp = N;
	for(int i = 1; i <= n; ++i) {
		ans += C(tmp, c[i]);
		tmp -= c[i];
	}
	tmp = n;
	for(int i = 1; i <= cnt; ++i) {
		ans += C(tmp, ct[i]);
		tmp -= ct[i];
	}
	ans -= num * N;
	printf("%.10lf", ans);
	return 0;
}
