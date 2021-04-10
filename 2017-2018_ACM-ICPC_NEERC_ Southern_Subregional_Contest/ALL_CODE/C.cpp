#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
ll f, T, t0;
ll a1, t1, p1;
ll a2, t2, p2;
int main() {
	scanf("%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d%I64d", &f, &T, &t0, &a1, &t1, &p1, &a2, &t2, &p2);
	if(f * t0 <= T) {
		puts("0");
		return 0;
	}
	ll tle = (ll) f * t0 - T;
	ll dt1 = t0 - t1;
	ll dt2 = t0 - t2;
	ll b1 = a1 * dt1;
	ll b2 = a2 * dt2;
	if(dt1 <= 0) {
		if(dt2 <= 0) {
			puts("-1");
			return 0;
		}
		ll k2 = tle / b2;
		ll c2 = (tle % b2 + dt2 - 1) / dt2;
		if(a2 * k2 + c2 <= f) printf("%I64d\n", p2 * k2 + (c2 ? p2 : 0));
		else puts("-1");
		return 0;
	}
	if(dt2 <= 0) {
		ll k1 = tle / b1;
		ll c1 = (tle % b1 + dt1 - 1) / dt1;
		if(a1 * k1 + c1 <= f) printf("%I64d\n", p1 * k1 + (c1 ? p1 : 0));
		else puts("-1");
		return 0;
	}
	ll ans = 1ll << 62;
	for(ll k1 = 0, r = min(f / a1, tle / b1); k1 <= r; k1++) {
		ll rem = tle - b1 * k1;
		ll k2 = rem / b2;
		ll c = (rem % b2 + dt2 - 1) / dt2;
		if(a1 * k1 + a2 * k2 + c <= f) ans = min(ans, p1 * k1 + p2 * k2 + (c ? p2 : 0));
	}
	swap(a1, a2);
	swap(t1, t2);
	swap(p1, p2);
	swap(dt1, dt2);
	swap(b1, b2);
	for(ll k1 = 0, r = min(f / a1, tle / b1); k1 <= r; k1++) {
		ll rem = tle - b1 * k1;
		ll k2 = rem / b2;
		ll c = (rem % b2 + dt2 - 1) / dt2;
		if(a1 * k1 + a2 * k2 + c <= f) ans = min(ans, p1 * k1 + p2 * k2 + (c ? p2 : 0));
	}
	if(ans == 1ll << 62) puts("-1");
	else printf("%I64d\n", ans);
	return 0;
}

