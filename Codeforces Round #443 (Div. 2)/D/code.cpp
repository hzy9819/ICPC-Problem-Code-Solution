#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define mk make_pair
#define fi first
#define se second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
LL read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, k, m, ans(0);
int a[N], sz(0), r(0);
pair <int, int> t[N];
int main() {
	Hzy("D");
	n = read(), k = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	int tmp = 0;
	for(int i = 1; i <= n; ++i) {
		tmp++;
		if(a[i] != a[i + 1] || i == n) {
			//ans += 2 * (tmp / k);
			tmp %= k;
			if(tmp) {
				if(sz && t[sz].fi == a[i]) {
					t[sz].se = (t[sz].se + tmp) % k;
					if(!t[sz].se) sz--;
				}
				else t[++sz] = mk(a[i], tmp);
			}
			tmp = 0;
		}
	}
	n = 0;
	for(int i = 1; i <= sz; ++i) n += t[i].se;
	if(m == 1) {
		//for(int i = 1; i <= sz; ++i) ans += t[i].se;
		printf("%I64d\n", n);
		return 0;
	}
	bool fg = 0;
	for(int i = 1; i <= sz; ++i)
		if((t[i].fi == t[sz - i + 1].fi) && ((t[i].se + t[sz - i + 1].se) >= k)) {
			r++;
			if(t[i].se + t[sz - i + 1].se > k) {
				fg = 1;
				r--;
				break;
			}
		}
		else break;
	if(r == sz) {
		if(m & 1) {
			for(int i = 1; i <= sz; ++i) ans += t[i].se;
			printf("%I64d\n", ans);
		}
		else puts("0");
	}
	else if((sz & 1) && r == sz / 2) {
		LL lev = (m * t[sz / 2 + 1].se) % k;
		ans = lev;
		if(ans != 0)
			//for(int i = 1; i <= sz / 2; ++i) ans += 2 * t[i].se;
			ans += k * (sz / 2);
		printf("%I64d\n", ans);
	}
	else {
		LL tmp = 0;
		for(int i = 1; i <= r; ++i) tmp += t[i].se;
		ans = (m - 2) * (n - 2LL * tmp) + 2LL * (n - tmp);
		if(fg) ans -= (m - 1) * k;
		printf("%I64d\n", ans);
		/*if(k == 2 && m == 1000) 
		  printf("%d %I64d", r, n);*/
	}
	return 0;
}
