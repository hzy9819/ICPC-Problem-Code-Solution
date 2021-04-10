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
const int N = 2000010;
int n, m;
LL dis[N], diss[N];
int lst[N], d, ans[N], tol;
bool vis[N];
struct Edge {
	int to, next, val;
}e[N];
void Init() {
	d = 0;
	memset(lst, -1, sizeof lst);
}
void add(int x, int y, int val) {
	e[d].to = y;
	e[d].val = val;
	e[d].next = lst[x];
	lst[x] = d++;
}
void Spfa(int s, LL * dis) {
	queue <int> Q;
	for(int i = 0; i <= n + m + 3; ++i) dis[i] = -1;
	memset(vis, 0, sizeof vis);
	dis[s] = 0;
	Q.push(s), vis[s] = 1;
	while(!Q.empty()) {
		LL tmp = Q.front();
		Q.pop();
		vis[tmp] = 0;
		for(int i = lst[tmp]; i >= 0; i = e[i].next) {
			LL temp = e[i].to, tp = e[i].val;
			if(dis[temp] == -1 || dis[temp] > dis[tmp] + tp) {
				dis[temp] = dis[tmp] + tp;
				if(!vis[temp]) {
					vis[temp] = 1;
					Q.push(temp);
				}
			}
		}
	}
}
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("M");
	int T = read(), cas = 0;
	int x, num, tt;
	while(T--) {
		cas++;
		n = read(), m = read();
		Init();
		for(int i = 1; i <= m; ++i) {
			tt = read(), num = read();
			for(int j = 1; j <= num; ++j) {
				x = read();
				add(x, i + n, tt);
				add(i + n, x, tt);
			}
		}
		Spfa(1, dis);
		printf("Case #%d: ", cas);
		if(dis[n] == -1) {
			puts("Evil John");
			continue;
		}
		Spfa(n, diss);
		tol = 0;
		LL res = -1;
		for(int i = 1; i <= n; ++i)
			if(res == -1 || max(dis[i], diss[i]) < res) res = max(dis[i], diss[i]);
		printf("%lld\n", res / 2);
		tol = 1;
		for(int i = 1; i <= n; ++i)
			if(max(dis[i], diss[i]) == res) ans[tol++] = i;
		for(int i = 1; i < tol; ++i)
			if(i == 1)
				printf("%d", ans[i]);
			else
				printf(" %d", ans[i]);
		puts("");
	}				
	return 0;
}
