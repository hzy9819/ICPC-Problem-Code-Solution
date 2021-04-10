#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 5010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, ans;
int a[N];
int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	int sz = 0;
	for(int i = 1; i <= n; ++i) {
		sz++;
		if(a[i] != a[i + 1]) ans = max(ans, sz), sz = 0;
	}
	printf("%d\n", ans);
	return 0;
}
