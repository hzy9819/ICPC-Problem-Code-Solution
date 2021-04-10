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
int n;
char s[N];
LL ans;
struct Node {
	LL x, y;
	bool operator < (const Node & p) const { return x * p.y < p.x * y; }
}a[N];
int main() {
	Hzy("D");
	n = read();
	LL x, y;
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s + 1);
		x = y = 0;
		for(int j = strlen(s + 1); j >= 1; --j) {
			if(s[j] == 's') ans += y, x++;
			else y++;
		}
		a[i].x = x, a[i].y = y;
	}
	sort(a + 1, a + n + 1);
	x = y = 0;
	for(int i = 1; i <= n; ++i) {
		ans += a[i].x * y;
		y += a[i].y;
	}
	printf("%lld\n", ans);
	return 0;
}
