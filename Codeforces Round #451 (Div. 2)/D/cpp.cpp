#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, k, a[N], ans;
bool vis[N];
int main() {
	Hzy("D");
	n = read(), m = read(), k = read();
	if(k <= 1) {
		printf("%d\n", n);
		return 0;
	}
	for(int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	int p = 0, now = 0;
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			while(p < n && a[i] + m > a[p + 1]) {
				now++, p++;
				if(now >= k) now--, vis[p] = 1, ans++;
			}
			now--;
		}
	printf("%d\n", ans);
	return 0;
}
