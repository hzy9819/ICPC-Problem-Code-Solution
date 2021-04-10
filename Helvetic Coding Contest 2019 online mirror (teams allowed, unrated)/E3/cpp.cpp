#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int M = 1000010;
const int INF = 1e9;
struct Edge {
	int to, next, w;
}e[N * 2];
int lst[N], d;

pair<pair<int, int>, pair<int, int> > ed[M];
int fa[N][20], f[N][20], dep[N];
int n, m, ans[M];
bool b[M];

void add(int x, int y, int w) {
	e[d].to = y, e[d].next = lst[x], e[d].w = w, lst[x] = d++;
}

int find_fa(int x) {
	if(fa[x][0] != x)
		fa[x][0] = find_fa(fa[x][0]);
	return fa[x][0];
}

int swim(int & x, int k) {
	int res = -1;
	for(int i = 19; i >= 0; --i)
		if(k & (1 << i))
			res = max(res, f[x][i]), x = fa[x][i];
	return res;
}

void dfs(int t, int pre) {
	int tmp = pre;
	fa[t][0] = pre, dep[t] = dep[pre] + 1;
	for(int j = 1; j < 20; ++j) {
		f[t][j] = max(f[t][j - 1], f[tmp][j - 1]);
		fa[t][j] = fa[tmp][j - 1], tmp = fa[tmp][j - 1];
		if(tmp <= 0)
			break;
	}
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != pre) {
			for(int j = 0; j < 20; ++j)
				f[e[i].to][j] = e[i].w;
			dfs(e[i].to, t);
		}
}

int Que(int x, int y) {
	if(dep[x] < dep[y])
		swap(x, y);
	int res = -1;
	res = max(res, swim(x, dep[x] - dep[y]));
	for(int i = 19; i >= 0; --i)
		if(fa[x][i] != fa[y][i]) {
			res = max(res, f[x][i]);
			res = max(res, f[y][i]);
			x = fa[x][i], y = fa[y][i];
		}
	if(x != y)
		res = max(res, max(f[x][0], f[y][0]));
	return res;
}

void Update(int x, int y, int w) {
	if(dep[x] < dep[y])
		swap(x, y);
	int k = dep[x] - dep[y];
	for(int i = 19; i >= 0; --i)
		if(k & (1 << i)) {
			if(f[x][i] == -1 || f[x][i] > w)
				f[x][i] = w;
			x = fa[x][i];
		}
	for(int i = 19; i >= 0; --i)
		if(fa[x][i] != fa[y][i]) {
			if(f[x][i] == -1 || f[x][i] > w)
				f[x][i] = w;
			if(f[y][i] == -1 || f[y][i] > w)
				f[y][i] = w;
			x = fa[x][i], y = fa[y][i];
		}
	if(x != y) {
		if(f[x][0] == -1 || f[x][0] > w)
			f[x][0] = w;
		if(f[y][0] == -1 || f[y][0] > w)
			f[y][0] = w;
	}
}
			

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("E");
	n = read(), m = read() ;
	for(int i = 0; i < m; ++i) 
		ed[i].r.l = read(), ed[i].r.r = read(), ed[i].l.l = read(), ed[i].l.r = i;
	sort(ed, ed + m);
	for(int i = 1; i <= n; ++i)
		fa[i][0] = i;
	int x, y, fx, fy;
	memset(lst, -1, sizeof lst);
	for(int i = 0; i < m; ++i) {
		x = ed[i].r.l, y = ed[i].r.r;
		fx = find_fa(x), fy = find_fa(y);
		if(fx != fy) {
			fa[fx][0] = fy;
			add(x, y, ed[i].l.l), add(y, x, ed[i].l.l);
			b[i] = 1;
		}
	}
	for(int i = 1; i <= n; ++i)
		fa[i][0] = 0;
	memset(f, -1, sizeof f);
	dfs(1, 0);
	for(int i = 0; i < m; ++i)
		if(!b[i])
			ans[ed[i].l.r] = Que(ed[i].r.l, ed[i].r.r);
	memset(f, -1, sizeof f);
	for(int i = 0; i < m; ++i)
		if(!b[i])
			Update(ed[i].r.l, ed[i].r.r, ed[i].l.l);
	for(int i = 19; i > 0; --i)
		for(int j = 1; j <= n; ++j)
			if(f[j][i] != -1) {
				int tmp = fa[j][i - 1];
				if(f[j][i - 1] == -1 || f[j][i - 1] > f[j][i])
					f[j][i - 1] = f[j][i];
				if(tmp && (f[tmp][i - 1] == -1 || f[tmp][i - 1] > f[j][i]))
					f[tmp][i - 1] = f[j][i];
			}
	for(int i = 0; i < m; ++i)
		if(b[i]) {
			x = ed[i].r.l, y = ed[i].r.r;
			if(fa[x][0] != y)
				swap(x, y);
			ans[ed[i].l.r] = f[x][0];
		}
	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i] == -1 ? INF : ans[i]);
	return 0;
}
