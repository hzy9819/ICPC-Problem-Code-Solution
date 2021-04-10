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
const int N = 100010;
const int weg = 1e9 + 7;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Mod(int & x, int y) {
	x += y;
	if(x >= weg) x -= weg;
}
int S, cod[20], col[20];
void decode(int * a, int n, int s) {
	for(int i = n; i >= 0; i--, s >>= 3)
		a[i] = s & 7;
}
int encode(int * a, int n) {
	int cnt = 0, s = 0;
	memset(col, -1, sizeof col), col[0] = 0;
	for(int i = 0; i <= n; ++i) {
		if(col[a[i]] == -1) col[a[i]] = ++cnt;
		a[i] = col[a[i]];
		s = (s << 3) | a[i];
	}
	return s;
}
struct Hash_Line {
	const static int H = 10010, N = 500010;
	int n, nxt[N], lst[H];
	int st[N], w[N], d[N];
	void Init() {
		n = 0;
		memset(lst, -1, sizeof lst);
	}
	void add(int _st, int _w, int _d) {
		int p = _st % H;
		for(int i = lst[p]; i >= 0; i = nxt[i])
			if(st[i] == _st) {
				if(_w < w[i]) {
					w[i] = _w, d[i] = _d;
				}
				else if(_w == w[i]) {
					Mod(d[i], _d);
				}
				return ;
			}
		st[n] = _st, w[n] = _w, d[n] = _d;
		nxt[n] = lst[p], lst[p] = n++;
	}	
}hs[2];
int n, m, v[810][8], h[810][8];

void dp(int x, int y, int t) {
	for(int i = 0; i < hs[t].n; ++i) {
		decode(cod, S, hs[t].st[i]);
		int U = cod[y], fg = 0;
		if(x == 0) fg = 1;
		else if(U > 0) {
			for(int j = 0; j < m; ++j)
				if(j != y && cod[j] == U) {
					fg = 1;
					break;
				}
		}
		if(x > 0 && U > 0) {
			hs[t ^ 1].add(hs[t].st[i], hs[t].w[i] + v[x][y], 2LL * hs[t].d[i] % weg);
		}
		if(y > 0 && fg) {
			decode(cod, S, hs[t].st[i]);
			cod[y] = cod[y - 1];
			hs[t ^ 1].add(encode(cod, S), hs[t].w[i] + h[x][y], 2LL * hs[t].d[i] % weg);
		}
		if(fg) {
			decode(cod, S, hs[t].st[i]);
			cod[y] = 14;
			hs[t ^ 1].add(encode(cod, S), hs[t].w[i], hs[t].d[i]);
		}
		if(x > 0 && y > 0 && cod[y - 1] != U) {
			decode(cod, S, hs[t].st[i]);
			int L = cod[y - 1];
			for(int j = 0 ; j < m; ++j)
				if(cod[j] == U)
					cod[j] = L;
			hs[t ^ 1].add(encode(cod, S), hs[t].w[i] + v[x][y] + h[x][y], 3LL * hs[t].d[i] % weg);
		}
	}
}
int main() {
	Hzy("E");
	int T = read(), cas = 0;
	while(T--) {
		cas++;
		n = read(), m = read(), S = m - 1;
		for(int i = 0 ; i < n; ++i)
			for(int j = 1; j < m; ++j)
				h[i][j] = read();
		for(int i = 1; i < n; ++i)
			for(int j = 0; j < m; ++j)
				v[i][j] = read();
		int t = 0;
		hs[t].Init();
		hs[t].add(0, 0, 1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				t ^= 1;
				hs[t].Init();
				dp(i, j, t ^ 1);
			}
		fill_n(cod, m, 1);
		int st = encode(cod, S);
		int mst = -1, deg = -1;
		for(int i = 0; i < hs[t].n; ++i)
			if(hs[t].st[i] == st)
				mst = hs[t].w[i], deg = hs[t].d[i];
		printf("Case #%d: %d %d\n", cas, mst, deg);
	}
	return 0;
}
