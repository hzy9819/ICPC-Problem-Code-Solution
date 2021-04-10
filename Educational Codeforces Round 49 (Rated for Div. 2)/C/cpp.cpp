#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1000010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int T, n, a[N], nm[N], ct[N], sz, cnt;
bool b;
int x, y;
int main() {
	Hzy("C");
	T = read();
	for(int i = 1; i <= T; ++i) {
		n = read();
		sz = 0, b = 0;
		for(int j = 1; j <= n; ++j) a[j] = read();
		sort(a + 1, a + n + 1);
		for(int j = 1; j <= n; ++j)
			if(a[j] != a[j - 1]) nm[++sz] = a[j], ct[sz] = 1;
			else ct[sz]++;
		cnt = sz;
		sz = 0;
		for(int j = 1; j <= cnt; ++j)
			if(ct[j] >= 2) nm[++sz] = nm[j], ct[sz] = ct[j];
		for(int j = 1; j <= sz; ++j)
			if(ct[j] >= 4) {
				for(int k = 1; k <= 4; ++k)
					printf("%d ", nm[j]);
				puts("");
				b = 1;
				break;
			}
		if(b) continue;
		x = nm[1], y = nm[2];
		for(int j = 3; j <= sz; ++j)
			if(y * nm[j - 1] > x * nm[j])
				x = nm[j - 1], y = nm[j];
		printf("%d %d %d %d\n", x, x, y, y);
	}
	return 0;
}
