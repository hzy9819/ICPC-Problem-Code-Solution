#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
const int M = 15;
const int LCM = 2600;

int gcd(int a, int b) {
	if(a < b)
		swap(a, b);
	int c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

int lcm(int a, int b) { return a * b / gcd(a, b); }

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, _lcm = 1;
int k[N], m[N], e[N][M];
int vis[N][LCM], b[N], cnt;

int dfs(int x, int y) {
	if(vis[x][y] > 0)
		return vis[x][y];
	if(vis[x][y] < 0) {
		int res = 0;
		for(int i = 1; i <= n; ++i)
			res += (b[i] <= vis[x][y]);
		return vis[x][y] = res;
	}
	vis[x][y] = b[x] = --cnt;
	return vis[x][y] = dfs(e[x][(y + k[x]) % m[x]], (y + k[x]) % _lcm);
}
	
int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		k[i] = read();
	for(int i = 1; i <= n; ++i) {
		m[i] = read();
		_lcm = lcm(_lcm, m[i]);
		for(int j = 0; j < m[i]; ++j)
			e[i][j] = read();
	}
	for(int i = 1; i <= n; ++i)
		k[i] = (k[i] % _lcm + _lcm) % _lcm;
	int q, x, y;
	q = read();
	while(q--) {
		x = read(), y = (read() % _lcm + _lcm) % _lcm;
		printf("%d\n", dfs(x, y));
	}
	return 0;
}
