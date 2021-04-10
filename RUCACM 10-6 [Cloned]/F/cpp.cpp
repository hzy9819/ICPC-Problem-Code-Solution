#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 100010;
LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL gcd(LL a, LL b) {
	LL c;
	if(a < b) swap(a, b);
	while(b)
		c = a % b, a = b, b = c;
	return a;
}
LL n, m;
LL fac[N], num[N], cnt, a[N];
LL calc(LL a, LL b) {
	return a * (a - 1) / 2 * b;
}

int main() {
	Hzy("F");
	int T = read(), cas = 0;
	while(T--) {
		cas++;
		n = read(), m = read();
		for(int i = 1; i <= n; ++i) a[i] = read();
		cnt = 0;
		memset(fac, 0, sizeof fac);
		memset(num, 0, sizeof num);
		for(LL i = 1; i * i <= m; ++i)
			if(m % i == 0) {
				fac[++cnt] = i;
				if(i * i != m) fac[++cnt] = m / i;
			}
		sort(fac + 1, fac + cnt + 1);
		for(int i = 1; i <= n; ++i) {
			LL tmp = gcd(a[i], m);
			for(int j = 1; j <= cnt; ++j)
				if(fac[j] % tmp == 0) num[j] = 1;
		}
		//num[cnt] = 0;
		LL ans = 0;
		for(int i = 1; i <= cnt; ++i)
			if(num[i]) {
				ans += num[i] * calc(m / fac[i], fac[i]);
				for(int j = i + 1; j <= cnt; ++j)
					if(fac[j] % fac[i] == 0) num[j] -= num[i];
			}
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
