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
int n, p;
LL ans;
struct Edge {
	int to, next, w;
}e[N * 2];
int list[N], d, fa[N];
void add(int x, int y, int w) {
	e[d].to = y, e[d].next = list[x], e[d].w = w, list[x] = d++;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL f[N], s[N];
int q[N], l, r;
bool calc(int i, int j, int w) { return 2LL * s[i] * (s[j] - s[w]) > f[j] - f[w] + s[j] * s[j] - s[w] * s[w];}
db Calc(int j, int w) {return 1.0 * (s[j] - s[w]) / (f[j] + s[j] * s[j] - f[w] - s[w] * s[w]);}
void dfs(int t) {
	for(int i = list[t]; i >= 0; i = e[i].next) if(!fa[e[i].to]) {
			fa[e[i].to] = t;
			s[e[i].to] = s[t] + e[i].w;
			dfs(e[i].to);
		}
}
void Dfs(int t) {
	int L, R, tmp;
	while(l < r && calc(t, q[l + 1], q[l])) l++;
	if(t != 1) f[t] = f[q[l]] + (s[t] - s[q[l]]) * (s[t] - s[q[l]]) + p;
	else f[t] = 0;
	ans = max(ans, f[t]);
	while(l < r && Calc(t, q[r]) > Calc(q[r], q[r - 1])) r--;
	if(t != 1) tmp = q[r + 1], q[++r] = t;
	L = l, R = r;
	for(int i = list[t]; i >= 0; i = e[i].next) if(e[i].to != fa[t]) {
			l = L, r = R;
			Dfs(e[i].to);
			l = L, r = R;
		}
	q[R] = tmp;
}
int main() {
	Hzy("I");
	int T = read(), x, y, z;
	while(T--) {
		n = read(), p = read(), ans = -1;
		d = 0;
		memset(list, -1, sizeof list);
		for(int i = 1; i < n; ++i) {
			x = read(), y = read(), z = read();
			add(x, y, z), add(y, x, z);
		}
		for(int i = 1; i <= n; ++i) fa[i] = 0;
		fa[1] = 1;
		dfs(1);
		//l = r = 1, q[1] = 1;
		l = r = 1, q[1] = 1;
		Dfs(1);
		printf("%lld\n", ans - p);
	}
	return 0;
}
