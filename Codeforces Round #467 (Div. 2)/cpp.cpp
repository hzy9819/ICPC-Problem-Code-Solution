#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
const int M = 200010;
struct Edge {
	int to, next;
}e[M], E[M];
int lst[N], d;
int Lst[N], D;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
void Add(int x, int y) {
	E[D].to = y, E[D].next = Lst[x], Lst[x] = D++;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
bool st[N][2], b[N], fg;
int dg[N], s;
int dfn[N], low[N], cnt, sta[N], sz;
bool Dfs(int t) {
	dfn[t] = ++cnt;
	low[t] = dfn[t];
	sta[++sz] = t;
	b[t] = 1;
	bool flag = 0;
	for(int i = Lst[t]; i >= 0; i = E[i].next) {
		if(dfn[E[i].to] && b[E[i].to]) low[t] = min(low[t], dfn[E[i].to]);
		else {
			flag = Dfs(E[i].to);
			if(flag) return 1;
			low[t] = min(low[t], low[E[i].to]);
		}
	}
	if(low[t] == dfn[t]) {
		if(sta[sz] != t) return 1;
		else sz--;
		b[t] = 0;
	}
	return 0;
}
void dfs(int t, int cur) {
	if(t == s && st[s][1]) {
		fg = 1;
		puts("Win");
		printf("%d ", t);
		return ;
	}
	if(fg) return ;
	bool flag = 0;
	for(int i = lst[t]; i >= 0; i = e[i].next) {
		flag = 0;
		if(!st[e[i].to][cur ^ 1]) st[e[i].to][cur ^ 1] = 1, flag = 1;
		//if(st[t][1] && !st[e[i].to][0]) st[e[i].to][0] = 1, flag = 1;
		if(flag) dfs(e[i].to, cur ^ 1);
		if(fg) {
			printf("%d ", t);
			return ;
		}
	}
}
int main() {
	Hzy("D");
	int x;
	n = read(), m = read();
	memset(lst, -1, 4 * (n + 1));
	memset(Lst, -1, 4 * (n + 1));
	for(int i = 1; i <= n; ++i) {
		dg[i] = read();
		for(int j = 1; j <= dg[i]; ++j)
			x = read(), add(x, i), Add(i, x);
	}
	s = read();
	for(int i = 1; i <= n; ++i)
		if(!dg[i]) {
			st[i][0] = 1;
			dfs(i, 0);
			if(fg) return 0;
		}	
	if(!st[s][0] && !st[s][1]) puts("Draw");
	else {
		if(Dfs(s)) puts("Draw");
		else puts("Lose");
	}
	return 0;
}
