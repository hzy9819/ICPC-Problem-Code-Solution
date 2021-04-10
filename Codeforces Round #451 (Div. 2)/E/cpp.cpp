#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
int n, a[N], w[N];
LL ans;
int calc(int x) {
	//if(x == 0) return 1;
	int l = sqrt(x), r = l + 1;
	return min(x - l * l, r * r - x);
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("E");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), w[i] = calc(a[i]);
	sort(w + 1, w + n + 1);
	for(int i = 1; i <= (n / 2); ++i) ans += w[i];
	if(ans == 0) {
		int tmp = 0;
		for(int i = (n / 2) + 1; i <= n; ++i) if(w[i] == 0) ans++;
		for(int i = 1; i <= n; ++i) if(a[i] == 0) tmp++;
		tmp = (n / 2) + ans - tmp;
		if(tmp < ans) ans += ans - tmp;
	}
	printf("%lld\n", ans);
	return 0;
}
