#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 110;
const int M = 5010;
int n, m;
struct Edge {
	int to, next, w;
}e[M];
int lst[N], d;
int f[N][N][26][2]; 
void add(int x, int y, int w) {
	e[d].to = y, e[d].next = lst[x], e[d].w = w, lst[x] = d++;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Dfs(int x, int y, int pre, int z) {
	if(f[x][y][pre][z]) return ;
	if(z == 0) {
		f[x][y][pre][z] = -1;
		for(int i = lst[x]; i >= 0; i = e[i].next)
			if(e[i].w >= pre) {
				if(!f[e[i].to][y][e[i].w][z ^ 1]) Dfs(e[i].to, y, e[i].w, z ^ 1);
				if(f[e[i].to][y][e[i].w][z ^ 1] == -1) f[x][y][pre][z] = 1;
			}
	}
	else {
		f[x][y][pre][z] = -1;
		for(int i = lst[y]; i >= 0; i = e[i].next)
			if(e[i].w >= pre) {
				if(!f[x][e[i].to][e[i].w][z ^ 1]) Dfs(x, e[i].to, e[i].w, z ^ 1);
				if(f[x][e[i].to][e[i].w][z ^ 1] == -1) f[x][y][pre][z] = 1;
			}
	}
}
int main() {
	Hzy("D");
	n = read(), m = read();
	int x, y; char z;
	memset(lst, -1, 4 * (n + 1));
	for(int i = 1; i <= m; ++i) {
		scanf("%d %d %c", &x, &y, &z);
		add(x, y, z - 'a');
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			Dfs(i, j, 0, 0);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j)
			if(f[i][j][0][0] == 1) printf("A");
			else printf("B");
		puts("");
	}
	return 0;
}
