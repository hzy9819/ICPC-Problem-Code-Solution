#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
struct Edge {
	int to, nxt, w;
}e[N * N];
int lst[N], d;
void add(int x, int y, int w) {
	e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

int n, m, s, k, c;

priority_queue <pair<int, int> > Q;

int dis[N];
bool b[N];

void Dij(int s, int * dis) {
	for(int i = 1; i <= n; ++i)
		dis[i] = -1, b[i] = 0;
	dis[s] = 0;
	Q.push(mk(0, s));
	while(!Q.empty()) {
		pair<int, int> tmp = Q.top();
		Q.pop();
		if(b[tmp.r])
			continue;
		b[tmp.r] = 1;
		for(int i = lst[tmp.r]; i >= 0; i = e[i].nxt)
			if(dis[e[i].to] == -1 || dis[e[i].to] > dis[tmp.r] + e[i].w) {
				dis[e[i].to] = dis[tmp.r] + e[i].w;
				Q.push(mk(-dis[e[i].to], e[i].to));
			}
	}
}

int d_min[N], p[N];
int h_max, p_max;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	int T = read();
	while(T--) {
		n = read(), m = read(), s = read(), k = read(), c = read();
		for(int i = 1; i <= k; ++i)
			p[i] = read();
		int x, y, w;
		memset(lst, -1, sizeof lst);
		d = 0;
		for(int i = 0; i < m; ++i) {
			x = read(), y = read(), w = read();
			add(x, y, w), add(y, x, w);
		}
		Dij(s, dis);
		h_max = p_max = 0;
		for(int i = 1; i <= n; ++i)
			h_max = max(h_max, dis[i]);
		memset(d_min, -1, sizeof d_min);
		for(int i = 1; i <= k; ++i) {
			Dij(p[i], dis);
			for(int j = 1; j <= n; ++j)
				if(j != p[i] && (d_min[j] == -1 || d_min[j] > dis[j]))
					d_min[j] = dis[j];
		}
		for(int i = 1; i <= n; ++i)
			p_max = max(p_max, d_min[i]);
		printf("%d\n", h_max <= p_max * c ? h_max : p_max);
	}
	return 0;
}
