#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, ans;
db cal;

LL pow_mod(LL a, LL n, LL p) {
	LL res = 1;
	while(n) {
		if(n & 1)
			res = res * a % p;
		a = a * a % p;
		n >>= 1;
	}
	return res;
}

db BBp(int n, LL k, LL b) {
	db res = 0;
	for(int i = 0; i <= n; ++i)
		res += (pow_mod(16, n - i, 8 * i + b) * 1.0 / (8 * i + b));
	for(int i = n + 1; i <= n + 1000; ++i)
		res += pow(16, n - i) * 1.0 / (8 * i + b);

	return k * res;
}

int main() {
	int T = read(), Cas = 0;
	while(T--) {
		++Cas;
		n = read();
		cal = BBp(n - 1, 4, 1) - BBp(n - 1, 2, 4) - BBp(n - 1, 1, 5) - BBp(n - 1, 1, 6);
		cal = cal - (int)cal;
		cal = (cal < 0 ? cal + 1.0 : cal);
		cal *= 16.;
		ans = (int) cal;
		printf("Case #%d: %d %c\n", Cas, n, (ans < 10 ? '0' + ans : 'A' + ans - 10));
	}
	return 0;
}
