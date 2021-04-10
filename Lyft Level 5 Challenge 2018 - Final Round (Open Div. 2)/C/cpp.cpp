#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, cnt = 0, ans = 0;
int a[N], b[N];
int p1 = 1, p2 = 1;
int main() {
	Hzy("C");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	int x, y, z;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read(), z = read();
		if(x == 1 && y == 1e9) ans++;
		else if(x == 1) b[++cnt] = y;
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + cnt + 1);
	while(p1 <= n && p2 <= cnt)
		if(b[p2] >= a[p1]) {
			ans++;
			p2++;
			p1++;
		}
		else
			p2++;
	cout << ans << endl;
	return 0;
}
