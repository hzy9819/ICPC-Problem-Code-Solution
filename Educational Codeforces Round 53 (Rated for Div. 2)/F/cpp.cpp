#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define mk(x, y) make_pair(x, y)
#define l first
#define r second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 200010;
const int M = 400010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int n;
int pre[N][2], ansp, sz[N], dep[N], st[N], cnt = 0;
pair<int, int> len[N], ans;
int fa[N], ml[N], prel[N][2];
pair<int, int> operator + (pair<int, int> x, pair<int, int> y) { return mk(x.l + y.l, x.r + y.r); }
void dfs(int t) {
	ml[t] = 0;
	prel[t][0] = prel[t][1] = 0;
	pre[t][0] = pre[t][1] = 0;
	sz[t] = 0;
	pair<int, int> p1, p2, tmp;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			dep[e[i].to] = dep[t] + 1;
			fa[e[i].to] = t;
			dfs(e[i].to) ;
			sz[t]++;
		}
	if(sz[t] == 1) {
		for(int i = lst[t]; i >= 0; i = e[i].next)
			if(e[i].to != fa[t]) {
				ml[t] = ml[e[i].to] + 1;
				prel[t][0] = e[i].to;
				if(len[e[i].to].r) {
					tmp = len[e[i].to];
					tmp.l++;
					len[t] = tmp;
					pre[t][0] = e[i].to;
				}
			}
	}
	else if(sz[t] > 1) {
		int l1 = 0, l2 = 0;
		p1 = p2 = mk(0, 0);
		for(int i = lst[t]; i >= 0; i = e[i].next)
			if(e[i].to != fa[t]) {
				if(ml[e[i].to] + 1 >= l1) {
					l2 = l1;
					prel[t][1] = prel[t][0];
					l1 = ml[e[i].to] + 1;
					prel[t][0] = e[i].to;
				}
				else if(ml[e[i].to] + 1 > l2) {
					l2 = ml[e[i].to] + 1;
					prel[t][1] = e[i].to;
				}
			}
		ml[t] = l1;
		for(int i = lst[t]; i >= 0; i = e[i].next)
			if(e[i].to != fa[t] && len[e[i].to].r) {
				tmp = len[e[i].to];
				tmp.l++;
				if(tmp >= p1) {
					p2 = p1;
					pre[t][1] = pre[t][0];
					p1 = tmp;
					pre[t][0] = e[i].to;
				}
				else if(tmp > p2) {
					p2 = tmp;
					pre[t][1] = e[i].to;
				}
			}
		if(p1.r && p2.r) {
			tmp = p1 + p2;
			if(tmp > ans) ans = tmp, ansp = t;
			len[t] = p1;
		}
		else if(p1.r && (sz[t] - 1 + (fa[t] ? 1 : 0)) >= 2) {
			l1 = l2 = 0;
			prel[t][0] = prel[t][1] = 0;
			if(fa[t]) {
				prel[t][0] = fa[t], l1 = dep[t];
				if(cnt > 1) {
					if(dep[t] + ml[t] != st[1]) l1 += st[2];
					else l1 += st[1];
				}
			}
			for(int i = lst[t]; i >= 0; i = e[i].next)
				if(e[i].to != fa[t] && e[i].to != pre[t][0]) {
					if(ml[e[i].to] + 1 >= l1) {
						l2 = l1;
						prel[t][1] = prel[t][0];
						l1 = ml[e[i].to] + 1;
						prel[t][0] = e[i].to;
					}
					else if(ml[e[i].to] + 1 > l2) {
						l2 = ml[e[i].to] + 1;
						prel[t][1] = e[i].to;
					}
				}
			tmp = mk(0, l1 + l2);
			tmp = tmp + p1;
			if(tmp > ans) ans = tmp, ansp = t;
			len[t] = p1;
		}
		else {
			len[t] = mk(0, l1 + l2);
		}
	}
}
bool cmp(const int & x, const int & y) { return x > y ; }
pair<int, int> ans1, ans2;
int main() {
	Hzy("F");
	n = read();
	int x, y;
	memset(lst, -1, sizeof lst);
	for(int i = 1; i < n; ++i) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	ml[0] = -1;
	dfs(1);
	for(int i = lst[1]; i >= 0; i = e[i].next)
		st[++cnt] = ml[e[i].to] + 1;
	sort(st + 1, st + cnt + 1, cmp);
	dfs(1);
	x = pre[ansp][0];
	while(pre[x][0]) x = pre[x][0];
	y = prel[x][1], x = prel[x][0];
	while(prel[x][0]) x = prel[x][0];
	while(prel[y][0]) y = prel[y][0];
	ans1 = mk(x, y);

	x = pre[ansp][1];
	if(x) {
		while(pre[x][0]) x = pre[x][0];
		y = prel[x][1], x = prel[x][0];
		while(prel[x][0]) x = prel[x][0];
		while(prel[y][0]) y = prel[y][0];
		ans2 = mk(x, y);
	}
	else {
		x = prel[ansp][0], y = prel[ansp][1];
		if(x == fa[ansp]) {
			if(cnt <= 1) x = 1;
			else {
				if(x == 1) x = ansp;
				while(fa[x] != 1) x = fa[x];
				int tpl = 0;
				for(int i = lst[1]; i >= 0; i = e[i].next)
					if(e[i].to != x && ml[e[i].to] > ml[tpl]) tpl = e[i].to;
				x = tpl;
				while(prel[x][0]) x = prel[x][0];
			}
		}						
		else while(prel[x][0]) x = prel[x][0];
		if(y == fa[ansp]) {
			if(cnt <= 1) y = 1;
			else {
				if(y == 1) y = ansp;
				while(fa[y] != 1) y = fa[y];
				int tpl = 0;
				for(int i = lst[1]; i >= 0; i = e[i].next)
					if(e[i].to != y && ml[e[i].to] > ml[tpl]) tpl = e[i].to;
				y = tpl;
				while(prel[y][0]) y = prel[y][0];
			}
		}
		else while(prel[y][0]) y = prel[y][0];
		ans2 = mk(x, y);
	}
		
	printf("%d %d\n%d %d\n", ans1.l, ans2.l, ans1.r, ans2.r);		
	return 0;
}
