#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, ans(0), bin[20], len, a[20];
int main() {
	Hzy("D");
	bin[0] = 1, len = 0;
	n = read();
	LL x = n, sum, num;
	while(x) {
		a[++len] = x % 10;
		bin[len] = bin[len - 1] * 10;
		x /= 10;
	}
	if(n < 5) 
		ans = n * (n - 1) / 2;
	else {
		if(len == 1) 
			ans = n == 9 ? n - 5 : n - 4;
		else if(a[len] >= 5) {
			ans = n - 5 * bin[len - 1] + 1;
			if(n == bin[len] - 1) ans--;
		}
		else {
			ans = a[len] * bin[len - 1] / 2;
			ans += (n - a[len] * bin[len - 1]) * a[len];
			if(a[len - 1] > 4) ans += (n - a[len] * bin[len - 1] - bin[len - 2] * 5 + 1);
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
