#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 300010;
const int weg = 998244353;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL n, a[N], b[N], ans = 1;
pair<int, int> c[N];

int main() {
	n = read();
	for(int i = 0; i < n; ++i) {
		a[i] = read(), b[i] = read();
		c[i] = mk(a[i], b[i]);
		ans = ans * (i + 1) % weg;
	}
	sort(a, a + n), sort(b, b + n), sort(c, c + n);
	LL cnt = 1, tmp = 1;
	for(int i = 1; i < n; ++i)
		if(a[i] == a[i - 1])
			tmp = tmp * cnt % weg, cnt++;
		else
			tmp = tmp * cnt % weg, cnt = 1;
	tmp = tmp * cnt % weg;
	ans = (ans - tmp + weg) % weg;
	cnt = 1, tmp = 1;
	for(int i = 1; i < n; ++i)
		if(b[i] == b[i - 1])
			tmp = tmp * cnt % weg, cnt++;
		else
			tmp = tmp * cnt % weg, cnt = 1;
	tmp = tmp * cnt % weg;
	ans = (ans - tmp + weg) % weg;
	bool fg = 1;
	int Lim = c[0].r;
	for(int i = 1; i < n; ++i)
		if(c[i].r < Lim)
			fg = 0;
		else
			Lim = c[i].r;
	if(fg) {
		cnt = 1, tmp = 1;
		for(int i = 1; i < n; ++i)
			if(c[i] == c[i - 1])
				tmp = tmp * cnt % weg, cnt++;
			else
				tmp = tmp * cnt % weg, cnt = 1;
		tmp = tmp * cnt % weg;
		ans = (ans + tmp) % weg;
	}
	cout << ans << endl;
	return 0;
}
