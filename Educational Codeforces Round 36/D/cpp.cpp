#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 510;
const int M = 100010;
struct Edge {
	int to, next;
}e[M];
int ls[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = ls[x], ls[x] = d++;
}
	
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
bool fg, ps[M];
int vis[N];
int n, m;
int st[N], tp, del;
inline void Dfs(int t) {
	if(fg) return ;
	vis[t] = 1;
	for(int i = ls[t]; i >= 0; i = e[i].next)
		if(!ps[i]) {
			if(fg) return ;
			ps[i] = 1;
			if(vis[e[i].to] == 1) {
				fg = 1;
				st[++tp] = i;
			}
			else {
				Dfs(e[i].to);
				if(fg) st[++tp] = i;
			}
		}
	vis[t] = -1;
}
inline void dfs(int t) {
	if(fg) return ;
	vis[t] = 1;
	for(int i = ls[t]; i >= 0; i = e[i].next) if(!ps[i]) {
			if(fg) return ;
			ps[i] = 1;
			if(vis[e[i].to] == 1) fg = 1;
			else dfs(e[i].to);
		}
	vis[t] = -1;
}
int main() {
	Hzy("D");
	n = read(), m = read();
	memset(ls, -1, 4 * (n + 1));
	int x, y;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		add(x, y);
	}
	for(int i = n ; i >= 1; --i)
		if(!vis[i] && !fg) Dfs(i);
	if(!fg) {
		puts("YES");
		return 0;
	}
	for(int i = 1; i <= tp; ++i) {
		memset(ps, 0, m + 1);
		ps[st[i]] = 1;
		memset(vis, 0, 4 *(n + 1));
		fg = 0;
		for(int j = 1; j <= n; ++j)
			if(!vis[j] && !fg) dfs(j);
		if(!fg) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
