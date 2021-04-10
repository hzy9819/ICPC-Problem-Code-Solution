#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 100050;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, q;
struct Edge {
	int to, next, d;
}e[N * 2];
struct edges {
	int x, y, d;
	bool operator < (const edges & p) const {
		return d < p.d;
	}
}ed[N + 100];
bool b[N + 100], bp[N];
int lst[N], d;
void add(int x, int y, int dis) {
	e[d].to = y, e[d].next = lst[x], e[d].d = dis, lst[x] = d++;
}
//vector < pair<int, int> > v[N];
int fa[N];
int find_fa(int x) {
	if(fa[x] != x) fa[x] = find_fa(fa[x]);
	return fa[x];
}
void merge(int i) {
	int fx = find_fa(ed[i].x), fy = find_fa(ed[i].y);
	if(fx != fy) {
		fa[fx] = fy;
		add(ed[i].x, ed[i].y, ed[i].d);
		add(ed[i].y, ed[i].x, ed[i].d);
		b[i] = 1;
	}
}
LL dis[45][N];
int FA[N][25], dep[N], bin[25], ct = 0;

void swim(int & x, int k) {
	for(int i = 20; i >= 0; --i)
		if(k & bin[i]) x = FA[x][i];
}

int lca(int x, int y) {
	if(dep[x] > dep[y]) swap(x, y);
	swim(y, dep[y] - dep[x]);
	if(x == y) return x;
	for(int i = 20; i >= 0; --i)
		if(FA[x][i] != FA[y][i])
			x = FA[x][i], y = FA[y][i];
	return FA[x][0];
}

int sta[N], sz;

void dfs(int t) {
	sta[++sz] = t;
	while(sz) {
		t = sta[sz--];
		for(int i = lst[t]; i >= 0; i = e[i].next)
			if(!FA[e[i].to][0]) {
				FA[e[i].to][0] = t;
				int tmp = t;
				for(int j = 1; j <= 20; ++j) {
					FA[e[i].to][j] = FA[tmp][j - 1];
					tmp = FA[tmp][j - 1];
				}
				dis[0][e[i].to] = dis[0][t] + e[i].d;
				dep[e[i].to] = dep[t] + 1;
				//dfs(e[i].to);
				sta[++sz] = e[i].to;
			}
	}
}

queue <int> Q;
bool inq[N];

void Spfa(int s, LL * dis) {
	for(int i = 1; i <= n; ++i) dis[i] = -1;
	dis[s] = 0;
	Q.push(s), inq[s] = 1;
	while(!Q.empty()) {
		int tmp = Q.front();
		Q.pop(), inq[tmp] = 0;
		for(int i = lst[tmp]; i >= 0; i = e[i].next)
			if(dis[e[i].to] == -1 || dis[e[i].to] > dis[tmp] + e[i].d) {
				dis[e[i].to] = dis[tmp] + e[i].d;
				if(!inq[e[i].to])
					Q.push(e[i].to), inq[e[i].to] = 1;
			}
	}
}

int main() {
	Hzy("F");
	n = read(), m = read();
	//int x, y, dis;
	bin[0] = 1;
	for(int i = 1; i <= 20; ++i)
		bin[i] = (bin[i - 1] << 1);
	memset(lst, -1, 4 * (n + 1));
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= m; ++i) {
		ed[i].x = read(), ed[i].y = read(), ed[i].d = read();
	}
	sort(ed + 1, ed + m + 1);
	for(int i = 1; i <= m; ++i)
		merge(i);
	FA[1][0] = 1;
	dfs(1);
	bp[1] = 1;
	for(int i = 1; i <= m; ++i)
		if(!b[i]) {
			add(ed[i].x, ed[i].y, ed[i].d);
			add(ed[i].y, ed[i].x, ed[i].d);
			bp[ed[i].x] = 1;
			bp[ed[i].y] = 1;
		}
	for(int i = 2; i <= n; ++i)
		if(bp[i])
			Spfa(i, dis[++ct]);
	q = read();
	int x, y, z;
	LL ans;
	for(int i = 1; i <= q; ++i) {
		x = read(), y = read();
		z = lca(x, y);
		ans = dis[0][x] + dis[0][y] - dis[0][z] * 2;
		for(int j = 1; j <= ct; ++j)
			ans = min(ans, dis[j][x] + dis[j][y]);
		cout << ans << endl;
	}
	return 0;
}
