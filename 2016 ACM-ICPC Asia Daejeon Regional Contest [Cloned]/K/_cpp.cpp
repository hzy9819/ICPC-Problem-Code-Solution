#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define l first
#define r second
#define mk make_pair
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 210;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
pair<int, int> a[N][N], s1[N], s2[N];
int ans[N][N];
int now1[N], now2[N];
bool fg;
void Out() {
	for(int i = 1; i <= n; ++i, puts(""))
		for(int j = 1; j <= m; ++j)
			printf("%d ", ans[i][j]);
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j)
			printf("%d ", a[i][j].l + ans[i][j]);
		printf("%d\n", a[i][m + 1].l + (now1[i] > 0 ? 1 : 0));
	}
	for(int i = 1; i <= m; ++i)
		printf("%d ", a[n + 1][i].l + (now2[i] > 0 ? 1 : 0));
	puts("");
}
void dfs(int i, int j) {
	if(fg) return ;
	if(j > m) dfs(i + 1, 1);
	if(i > n) {
		fg = 1;
		Out();
	}
	if(a[i][j].r == 0) dfs(i, j + 1);
	else {
		ans[i][j] = 0;
		now1[i] -= a[i][j].r;
		now2[j] -= a[i][j].r;
		s1[i].l -= a[i][j].r, s1[i].r -= 10 - a[i][j].r;
		s2[j].l -= a[i][j].r, s2[j].r -= 10 - a[i][j].r;
		if((now1[i] + s1[i].r >= -a[i][m + 1].r || now1[i] - s1[i].l <= 10 - a[i][m + 1].r) && (now2[j] + s2[j].r >= -a[n + 1][j].r || now2[j] - s2[j].l <= 10 - a[n + 1][j].r))
			dfs(i, j + 1);
		now1[i] += 10;
		now2[j] += 10;
		ans[i][j] = 1;
		if((now1[i] + s1[i].r > -10 || now1[i] - s1[i].l < 10) && (now2[j] + s2[j].r > -10 || now2[j] - s2[j].l < 10))
			dfs(i, j + 1);
		now1[i] -= 10 - a[i][j].r;
		now2[j] -= 10 - a[i][j].r;
		s1[i].l += a[i][j].r, s1[i].r += 10 - a[i][j].r;
		s2[j].l += a[i][j].r, s2[j].r += 10 - a[i][j].r;
	}
}

int main() {
	Hzy("K");
	while(cin >> n >> m) {
		fg = 0;
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m + 1; ++j)
				a[i][j].l = read(), a[i][j].r = read(), ans[i][j] = 0;
		}
		for(int i = 1; i <= m; ++i)
			a[n + 1][i].l = read(), a[n + 1][i].r = read();
		for(int i = 1; i <= n; ++i) s1[i] = mk(0, 0), now1[i] = 0;
		for(int i = 1; i <= m; ++i) s2[i] = mk(0, 0), now2[i] = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(a[i][j].r != 0) {
					s1[i].l += a[i][j].r;
					s1[i].r += 10 - a[i][j].r;
					s2[j].l += a[i][j].r;
					s2[j].r += 10 - a[i][j].r;
				}
		dfs(1, 1);
	}	   
	return 0;
}
