#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
int read() {
	int f = 0, w = 0; char c = getchar();
	while((c != '-') && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Edge {
	int to, next;
}e[N];
int list[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = list[x], list[x] = d++;
}
int din[N], dout[N];
vector <int> a[N];
struct edges {
	int x, y;
}ed[N];
int n, m;
int col[N], fa[N], next[N], cnt;
void Imp() {
	puts("There is no route, Karl!");
	exit(0);
}
void Simplify(int t) {
	col[t] = ++cnt;
	while(din[t] == 1 && fa[t] && dout[fa[t]] == 1 && !col[fa[t]]) t = fa[t], col[t] = cnt;
	//	if(!din[fa[t]]) Imp();
	int hd = t;
	do {
		col[t] = cnt;
		a[cnt].push_back(t);
		if(dout[t] > 1) break;
		t = next[t];
		if(din[t] > 1) break;
	}while(t != hd);
	
}
	
void Simplify_Edges() {
	memset(list, -1, 4 * (n + 1));
	for(int i = 1; i <= n; ++i)
		if(!col[i])
			Simplify(i);
	int x, y;
	for(int i = 1; i <= m; ++i) {
		x = ed[i].x, y = ed[i].y;
		if(col[x] == col[y]) continue;
		add(col[x], col[y]);
	}
}
bool vis[N];
int ans[N], temp[N];
void Out() {
	int ct = 0;
	for(int i = 0; i < cnt; ++i)
		for(size_t j = 0; j < a[ans[i]].size(); ++j)
			temp[++ct] = a[ans[i]][j];
	for(int i = 1; i <= ct; ++i)
		if(temp[i] == 1) {
			for(int j = i; j <= ct; ++j)
				printf("%d ", temp[j]);
			for(int j = 1; j <= i; ++j)
				printf("%d ", temp[j]);
			break;
		}
	//printf("%d ", a[col[1]][0]);
	exit(0);
}
void dfs(int t, int sum) {
	if(sum == cnt) Out();
	if(0 < sum && sum < cnt && t == col[1]) return ;
	for(int i = list[t]; i >= 0; i = e[i].next) {
		int u = e[i].to;
		if(!vis[u]) {
			vis[u] = 1;
			ans[sum + 1] = u;
			dfs(u, sum + 1);
			vis[u] = 0;
		}
	}
}
int main() {
	Hzy("king");
	n = read(), m = read();
	for(int i = 1; i <= m; ++i)
		ed[i].x = read(), ed[i].y = read(),
			din[ed[i].y]++, dout[ed[i].x]++,
			fa[ed[i].y] = ed[i].x, next[ed[i].x] = ed[i].y;
	for(int i = 1; i <= n; ++i)
		if(!din[i] || !dout[i]) Imp();
	Simplify_Edges();
	ans[0] = col[1];
	if(cnt == 1) Out();
	dfs(col[1], 0);
	Imp();
	return 0;
}
