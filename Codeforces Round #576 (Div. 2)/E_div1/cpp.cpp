#include <bits/stdc++.h>
#define LL long long
#define db double
#define mk(a, b) make_pair(a, b)
#define l first
#define r second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

const int N = 210;
const int M = 30010;

int n, m, cnt1, cnt2, S, T;
bool vis[N][N];
struct Cor {
	int x1, y1, x2, y2;
}cor[N];

int c_x[N], c_y[N];

struct Edge {
	int to, next, w;
}e[M];
int lst[N], d;

void add(int x, int y, int w) {
	e[d].to = y, e[d].next = lst[x], e[d].w = w, lst[x] = d++;
	e[d].to = x, e[d].next = lst[y], e[d].w = 0, lst[y] = d++;
}


int iter[N], dis[N];
queue <int> Q;

inline int Bfs(Edge * e, int * lst, int S, int T) {
	for(int i = 0; i <= T; ++i)
		dis[i] = 0, iter[i] = lst[i];
	dis[S] = 1, Q.push(S);
	while(!Q.empty()) {
		int x = Q.front(); Q.pop();
		for(int i = lst[x]; i >= 0; i = e[i].next)
			if(!dis[e[i].to] && e[i].w) 
				dis[e[i].to] = dis[x] + 1, Q.push(e[i].to);		
	}
	return dis[T];
}

int Dfs(Edge * e, int * lst, int T, int x, int f) {
	if(x == T || !f)
		return f;
	int sf = 0;
	for(int i = iter[x]; i >= 0; i = e[i].next)
		if(dis[e[i].to] == dis[x] + 1 && e[i].w) {
			int w = Dfs(e, lst, T, e[i].to, min(e[i].w, f));
			if(f) {
				e[i].w -= w;
				e[i ^ 1].w += w;
				f -= w, sf += w;
			}
		}
	return sf;
}
				

int Dinic(Edge * e, int * lst, int S, int T) {
	int ans = 0;
	while(Bfs(e, lst, S, T))
		ans += Dfs(e, lst, T, S, 1e9);
	return ans;
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
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		cor[i].x1 = read(), cor[i].y1 = read(), cor[i].x2 = read()+ 1, cor[i].y2 = read() + 1;
		c_x[cnt1++] = cor[i].x1, c_x[cnt1++] = cor[i].x2;
		c_y[cnt2++] = cor[i].y1, c_y[cnt2++] = cor[i].y2;
	}
	sort(c_x, c_x + cnt1); cnt1 = unique(c_x, c_x + cnt1) - c_x;
	sort(c_y, c_y + cnt2); cnt2 = unique(c_y, c_y + cnt2) - c_y;
	memset(lst, -1, sizeof lst), d = 0;
	S = cnt1 + cnt2, T = S + 1;
	for(int i = 0; i < cnt1 - 1; ++i)
		add(S, i, c_x[i + 1] - c_x[i]);
	for(int i = 0; i < cnt2 - 1; ++i)
		add(cnt1 + i, T, c_y[i + 1] - c_y[i]);
	for(int i = 1; i <= m; ++i) {
		int lx = lower_bound(c_x, c_x + cnt1, cor[i].x1) - c_x;
		int rx = lower_bound(c_x, c_x + cnt1, cor[i].x2) - c_x;
		int ly = lower_bound(c_y, c_y + cnt2, cor[i].y1) - c_y;
		int ry = lower_bound(c_y, c_y + cnt2, cor[i].y2) - c_y;
		for(int x = lx; x < rx; ++x)
			for(int y = ly; y < ry; ++y)
				if(!vis[x][y])
					vis[x][y] = 1, add(x, cnt1 + y, 1e9);
	}
	printf("%d\n", Dinic(e, lst, S, T));
	return 0;
}
