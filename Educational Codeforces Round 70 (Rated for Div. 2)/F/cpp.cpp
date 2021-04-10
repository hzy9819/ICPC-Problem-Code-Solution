#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL a, b, n, ans = 0;
int main() {
	a = read(), b = read();
	n = a + b;
	LL l = 1, r, g;
	while(l <= n) {
		g = n / l;
		if(g > a || g > b) {
			l = n / g + 1;
			continue;
		}
		r = n / g;
		LL a_low = (a + g) / (g + 1);
		LL a_hi = a / g;
		LL b_low = (b + g) / (g + 1);
		LL b_hi = b / g;
		if(a_hi >= a_low && b_hi >= b_low)
			ans += min(r, a_hi + b_hi) - max(l, a_low + b_low) + 1;
		l = r + 1;
	}
	cout << ans << endl;
	return 0;
}
