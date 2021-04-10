#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
struct Num {
	int x, y, z;
	bool operator < (const Num & p) const {
		return z < p.z;
	}
}a[10];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int sum[4], m;
int num[4], cnt, c[N];
bool check(int lim) {
	int tmp[4];
	for(int i = 1; i <= 3; ++i) tmp[i] = sum[i];
	for(int i = 1; i <= m; ++i) {
		bool fg = 0;
		for(int j = 1; j <= cnt; ++j) if(!tmp[a[j].x] || !tmp[a[j].y] || c[i] * a[j].z < lim || (a[j].x == a[j].y && tmp[a[j].x] < 2)) continue;
			else {
				fg = 1;
				tmp[a[j].x]--, tmp[a[j].y]--;
				break;
			}
		if(!fg) return false;
	}
	return true;
}
int main() {
	Hzy("K");
	//b = read(), n = read(), e = read();
	//sb = read(), sn = read(), se = read();
	for(int i = 1; i <= 3; ++i) sum[i] = read();
	for(int i = 1; i <= 3; ++i) num[i] = read();
	//a[1] = (Num){1, 2, num[1] + num[2]};
	//a[2] = (Num){2, 3, num[2] + num[3]};
	//a[3] = (Num){1, 3, num[1] + num[3]};
	for(int i = 1; i <= 3; ++i)
		for(int j = i; j <= 3; ++j) a[++cnt] = (Num){i, j, num[i] + num[j]};
	m = (sum[1] + sum[2] + sum[3]) / 2;
	for(int i = 1; i <= m; ++i) c[i] = read();
	sort(c + 1, c + m + 1);
	sort(a + 1, a + 4);
	int l, r, mid;
	for(l = 0, r = 2e8, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	}
	printf("%d\n", l - 1);
	return 0;
}
