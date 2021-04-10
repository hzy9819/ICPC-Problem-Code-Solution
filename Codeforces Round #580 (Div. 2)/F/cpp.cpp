#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}

int fa[N], n, sz[N];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void dfs1(int t) {
	sz[t] = 1;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			fa[e[i].to] = t;
			dfs1(e[i].to);
			sz[t] += sz[e[i].to];
		}
}

void dfs2(int t, int num, int mul) {
	int tmp = 0;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			printf("%d %d %d\n", t, e[i].to, (tmp + 1) * mul);
			dfs2(e[i].to, sz[e[i].to] - 1, mul);
			tmp += sz[e[i].to];
		}
}
			

vector <pair<int, int> > Sz;
			

int main() {
	n = read();
	if(n == 1)
		return 0;
	memset(lst, -1, sizeof lst);
	int x, y;
	for(int i = 1; i < n; ++i) {
		x = read(), y = read();
		add(x, y);
		add(y, x);
	}
	int Lim = (n + 1) / 3;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			fa[j] = 0;
		fa[i] = i;
		dfs1(i);
		Sz.clear();
		for(int j = lst[i]; j >= 0; j = e[j].next)
			Sz.push_back(mk(sz[e[j].to], e[j].to));
		sort(Sz.begin(), Sz.end());
		int sm = 0;
		size_t now = 0;
		for(now = 0; now < Sz.size(); ++now) {
			sm += Sz[now].l;
			if(sm * (n - sm) >= 2 * n * n / 9)
				break;
		}
		if(sm * (n - sm) < 2 * n * n / 9)
			continue;
		int tmp = 0;
		for(size_t j = 0; j <= now; ++j) {
			printf("%d %d %d\n", i, Sz[j].r, tmp + 1);
			dfs2(Sz[j].r, Sz[j].l - 1, 1);
			tmp = tmp + Sz[j].l;
		}
		tmp = 0;
		for(size_t j = now + 1; j < Sz.size(); ++j) {
			printf("%d %d %d\n", i, Sz[j].r, (tmp + 1) * (sm + 1));
			dfs2(Sz[j].r, Sz[j].l - 1, sm + 1);
			tmp = tmp + Sz[j].l;
		}
		break;
	}
	return 0;
}
