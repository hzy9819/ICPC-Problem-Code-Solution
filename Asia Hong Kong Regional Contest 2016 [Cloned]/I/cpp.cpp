#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 40010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Edge {
	int to, next;
}e[N * 10];
int lst[N], d;
bool vis[N];
int dis[N];
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int n, m;
int calc(int x, int y) { return (x - 1) * m + y; }
bool OK(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > m) return 0;
	return 1;
}
int st[N];
void Output() {
	for(int i = 1; i <= n * m; ++i)
		printf("%d %d\n", st[i] / m + 1, st[i] % m + 1);
}
void dfs(int t, int len) {
	vis[t] = 1;
	dis[t] = len;
	st[len] = t;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(!vis[e[i].to]) {
			dfs(e[i].to, len + 1);
		}
		else {
			if(t == 1 && len == n * m) {
				Output();
				exit(0);
			}
		}
}
			

int main() {
	Hzy("I");
	n = read(), m = read();
	memset(lst, -1, 4 * (n * m) + 1);
	int x, y;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			x = i + 2, y = j;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i + 1, y = j + 1;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i, y = j + 2;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i + 3, y = j;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i + 2, y = j + 1;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i + 1, y = j + 2;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
			x = i, y = j + 3;
			if(OK(x, y)) add(calc(i, j), calc(x, y)), add(calc(x, y), calc(i, j));
		}
	dfs(1, 1);
	puts("-1");
	return 0;
}
