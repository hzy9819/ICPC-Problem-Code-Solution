#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
const int K = 110;

vector <LL> v[N];
vector <pair<int, int> > Q[N];
LL ans[N];
int n, a[N], q;

struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d, fa[N], maxd[N];
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void dfs(int t, int f) {
	fa[t] = f;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != f)
			dfs(e[i].to, t);
}

void Dfs(int t) {
	v[t].resize(maxd[t] + 1);
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			maxd[e[i].to] = max(maxd[t] - 1, maxd[e[i].to]);
			Dfs(e[i].to);
			for(int j = 1; j <= maxd[e[i].to]; ++j)
				v[t][j] += v[e[i].to][j - 1];
			for(int j = maxd[e[i].to] + 1; j <= maxd[t]; ++j)
				v[t][j] += v[e[i].to][maxd[e[i].to]];
			vector<LL>().swap(v[e[i].to]);
		}
	for(int i = 1; i <= maxd[t]; ++i) 
		if(!v[t][i])
			v[t][i] = v[t][i - 1];
	for(int i = 0; i <= maxd[t]; ++i)
		v[t][i] += a[t];
	int x, y;
	for(size_t i = 0; i < Q[t].size(); ++i) {
		x = Q[t][i].l, y = Q[t][i].r;
		ans[abs(y)] += y > 0 ? v[t][x] : -v[t][x];
	}
}
	
	

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	memset(lst, -1, sizeof lst);
	int x, y;
	for(int i = 1; i < n; ++i)
		x = read(), y = read(), add(x, y), add(y, x);
	dfs(1, -1);
	q = read();
	for(int i = 1; i <= q; ++i) {
		x = read(), y = read();
		while(x > 1 && y >= 0) {
			Q[x].push_back(mk(y, i));
			maxd[x] = max(maxd[x], y);
			if(y >= 2) {
				Q[x].push_back(mk(y - 2, -i));
				maxd[x] = max(maxd[x], y - 2);
			}
			y--;
			x = fa[x];
		}
		if(x > 0 && y >= 0) {
			Q[x].push_back(mk(y, i));
			maxd[x] = max(maxd[x], y);
		}
	}
	Dfs(1);
	for(int i = 1; i <= q; ++i)
		printf("%lld ", ans[i]);
	return 0;
}
