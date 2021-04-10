#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL x[N], a[N], n, m;
LL s[N];

int main() {
	n = read(), m = read();
	for(int i = 0; i < m; ++i)
		x[i] = read();
	int l, r;
	for(int i = 1; i < m; ++i) {
		l = x[i - 1], r = x[i];
		if(l > r)
			swap(l, r);
		if(l == r)
			continue;
		a[1] += r - l;
		if(r - l > 1)
			a[l + 1]--, a[r]++;
		a[l] += r - 1 - (r - l), a[l + 1] -= r - 1 - (r - l);
		a[r] += l - (r - l), a[r + 1] -= l - (r - l);
	}
	for(int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + a[i];
	for(int i = 1; i <= n; ++i)
		printf("%lld ", s[i]);
	return 0;
}
