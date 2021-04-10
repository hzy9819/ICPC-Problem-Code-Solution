#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
vector <int> dfn, low, S, vis, col, a[N];
int cnt, num;
void tarjan(int t, int pre = -1) {
	low[t] = dfn[t] = ++cnt;
	vis[t] = 1;
	S.push_back(t) ;
	for(auto i : a[t]) {
		if(i == pre) continue;
		if(dfn[i] == -1)
			tarjan(i, t);
		if(vis[i])
			low[t] = min(low[t], low[i]);
	}
	if(low[t] == dfn[t]) {
		num++;
		while(1) {
			int x = S.back(); S.pop_back(); vis[x] = 0;
			col[x] = num;
			if(x == t) break;
		}
	}
}
void dij(int s, LL * d, vector< tuple<int, int, int>> e[N]) {
	fill(d, d + N, inf);
	d[s] = 0;
	priority_queue< pair<LL, int> > Q;
	Q.emplace(-d[s], s);
	while(!Q.empty()) {
		LL ct; int now;
		tie(ct, now) = Q.top(), Q.pop();
		ct = -ct;
		if(d[now] != ct) continue;
		for(auto it : e[now]) {
			LL add; int nx;
			tie(nx, add, ignore) = it;
			LL nct = ct + add;
			if(nct < d[nx]) {
				d[nx] = nct;
				Q.emplace(-d[nx], nx);
			}
		}
	}
}
LL d[N], drev[N];
int u[N], v[N], w[N];
vector< tuple<int, int, int>> e[N];
vector< tuple<int, int, int>> rev[N];
bool posb[N], done[N];

void dfs(int t) {
	if(done[t]) return ;
	done[t] = 1;
	for(auto it : rev[t]) {
		int to, ct, id;
		tie(to, ct, id) = it;
		if(d[to] + ct == d[t]) {
			posb[id] = 1;
			dfs(to);
		}
	}
}

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("F");
	int n, m;
	n = read(), m = read();
	for(int i = 0; i < m; ++i) {
		u[i] = read(), v[i] = read(), w[i] = read();
		e[u[i]].emplace_back(v[i], w[i], i);
		rev[v[i]].emplace_back(u[i], w[i], i);
	}
	dij(1, d, e);
	dij(2, drev, rev);

	dfs(2);
	for(int i = 0; i < m; ++i) {
		if(posb[i]) {
			a[u[i]].push_back(v[i]);
			a[v[i]].push_back(u[i]);
		}
	}
	dfn.assign(n + 1, -1);
	low.assign(n + 1, 0);
	vis.assign(n + 1, 0);
	col.assign(n + 1, -1);
	cnt = num = 0;
	for(int i = 1; i <= n; ++i)
		if(dfn[i] == -1)
			tarjan(i);

	for(int i = 0; i < m; ++i) {
		if(d[v[i]] + drev[u[i]] + w[i] < d[2])
			puts("HAPPY");
		else if(posb[i] && col[u[i]] != col[v[i]])
			puts("SAD");
		else
			puts("SOSO");
	}
	return 0;
}
