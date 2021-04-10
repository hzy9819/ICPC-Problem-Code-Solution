#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 300010;
struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, q, rm[N];
bool in[N], vis[N];
struct Pr {
	int l, r;
}s[N * 2];
int sz, fa[N], col[N];
void dfs(int t) {
	vis[t] = 1;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(!vis[e[i].to]) {
			fa[e[i].to] = t;
			dfs(e[i].to);
		}
		else if(e[i].to != fa[t] && !col[e[i].to]) {
			++sz;
			s[sz].l = s[sz].r = t;
			col[t] = sz;
			for(int j = t; j != e[i].to; j = fa[j]) {
				col[fa[j]] = sz;
				s[sz].l = min(s[sz].l, fa[j]);
				s[sz].r = max(s[sz].r, fa[j]);
			}
		}
}
bool cmp(const Pr & x, const Pr & y) {return x.r < y.r;}
LL sum[N];
int main() {
	Hzy("E");
	n = read(), m = read();
	int x, y;
	memset(lst, -1, 4 * (n + 1)), d = 0;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i);
	sort(s + 1, s + sz + 1, cmp);
	int p = 1; LL tmp, ans;
	for(int i = 1; i <= n; ++i) {
		while(p <= sz && s[p].l < i) p++;
		if(p > sz) rm[i] = n;
		else rm[i] = s[p].r - 1;
		sum[i] = sum[i - 1] + (rm[i] - i + 1);
	}
	q = read();
	for(int i = 1, l, r, mid; i <= q; ++i) {
		x = read(), y = read();
		for(l = x, r = y, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
			if(rm[mid] < y) l = mid + 1;
			else r = mid - 1;
		tmp = y - l + 1;
		ans = sum[l - 1] - sum[x - 1] + tmp * (tmp + 1) / 2;
		printf("%I64d\n", ans);
	}
	return 0;
}
