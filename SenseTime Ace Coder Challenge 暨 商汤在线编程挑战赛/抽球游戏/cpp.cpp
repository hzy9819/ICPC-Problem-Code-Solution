#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 110;
int T, n, p[N];
int num[N], sum[N];
bool fg;
struct Num {
	int x, y;
	bool operator < (const Num & p) const {
		return y > p.y;
	}
}a[N];
int calc(int x) {
	int s = 0;
	while(x) {
		s += (x & 1);
		x >>= 1;
	}
	return s;
}
void Im(int t) {
	printf("Case #%d: -1\n", t);
	fg = 1;
}
int cc(int x){
    return 4 * x * x * x - 6 * n * x * x + 3 * n * n * x;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("C");
	T = read();
	for(int i = 0; i <= 63; ++i) a[i].x = i, a[i].y = calc(i);
	sort(a, a + 64);
	for(int tc = 1; tc <= T; ++tc) {
		n = read(), fg = 0;
		for(int i = 0; i <= 63; ++i) p[i] = read(), num[i] = 0, sum[i] = 0;
		for(int i = 0; i <= 63; ++i) {
			for(int j = 0; j <= 63; ++j)
				if((i & j) == i) num[i] += p[j];
			/*if(num[i] % (n * n) != 0) Im(tc);
			if(fg) break;
			num[i] /= (n * n);*/
			num[i] = cc(num[i]);
		}
		if(fg) continue;
		for(int i = 63; i >= 0; --i) {
			sum[a[i].x] = num[a[i].x];
			for(int j = 0; j <= 63; ++j)
				if((j & a[i].x) == j) {
					num[j] -= sum[a[i].x];
					if(num[j] < 0) Im(tc);
				}
			if(fg) break;
		}
		if(fg) continue;
		printf("Case #%d: ", tc);
		for(int i = 0; i <= 63; ++i)
			for(int j = 1; j <= sum[i]; ++j)
				printf("%d ", i);
		puts("");
	}
	return 0;
}
