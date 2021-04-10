#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 510;
struct Node {
	int x, y;
};
int n, m;
int a[N][N], c[N][N];
bool b[N][N], vis[N][N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL ans;
deque <Node> Q;
void BFS() {
	int x, y; Node tmp;
	while(!Q.empty()) {
		tmp = Q.front(), Q.pop_front();
		b[tmp.x][tmp.y] = 0;
		for(int i = -1; i <= 1; ++i)
			for(int j = -1; j <= 1; ++j) if(i || j) {
					x = tmp.x + i, y = tmp.y + j;
					if(x < 1 || x > n || y < 1 || y > m) continue;
					if(a[x][y] >= 0) continue;
					if(c[x][y] != a[x][y] && c[x][y] > c[tmp.x][tmp.y]) {
						c[x][y] = max(a[x][y], c[tmp.x][tmp.y]);
						if(!b[x][y]) {
							b[x][y] = 1;
							if(Q.empty() || c[x][y] < c[Q.front().x][Q.front().y]) Q.push_front((Node) {x, y}); 
							else Q.push_back((Node) {x, y});
						}
					}
							/*if(!vis[x][y] && !b[x][y]) {
						b[x][y] = 1, vis[x][y] = 1;
						Q.push((Node) {x, y});
						}*/
				}
	}
}
int main() {
	Hzy("E");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) 
			a[i][j] = read();
	int x, y;
	x = read(), y = read(), c[x][y] = a[x][y];
	b[x][y] = 1;
	Q.push_front((Node) {x, y});
	/*for(int i = 1; i <= n; ++i)
	  for(int j = 1; j <= m; ++j) c[i][j] = max(a[x][y], c[i][j]);*/
	BFS();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) if(c[i][j] < 0) ans += -c[i][j];
	printf("%I64d\n", ans);
	return 0;
}
