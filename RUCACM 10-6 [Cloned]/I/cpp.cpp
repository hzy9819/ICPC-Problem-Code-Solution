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
const int N = 1010;
const int M = 100010;
const int LIM = 1000;
LL c[N][N];
int n, m, mp[M];
LL num[M];
struct Node {
	int a, b, c; LL sum;
	Node() {}
	Node(int _a, int _b, int _c, LL _sum) : a(_a), b(_b), c(_c), sum(_sum) {}
	bool operator < (const Node & p) const {
		if(p.a != a) return a < p.a;
		else if(p.b != b) return b < p.b;
		else return c < p.c;
	}
	Node operator + (const Node & p) const { return Node(a, b, c, sum + p.sum); }
	bool operator == (const Node & p) const { return a == p.a && b == p.b && c == p.c; }
}st[M];
void add(int x, int y, LL d) {
	int _y = y;
	for(; x < N; x += x & (-x))
		for(y = _y ; y < N; y += y & (-y))
			c[x][y] += d;
}
LL Que(int x, int y) {
	LL res = 0;
	int _y = y;
	for(; x > 0; x -= x & (-x))
		for(y = _y ; y > 0; y -= y & (-y))
			res += c[x][y];
	return res;
}
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("I");
	int T = read(), cas = 0;
	while(T--) {
		cas++;
		n = read(), m = read();
		memset(c, 0, sizeof c);
		memset(mp, 0, sizeof mp);
		memset(num, 0, sizeof num);
		int x, y, z;
		for(int i = 0 ; i < n; ++i) {
			x = read(), y = read();
			if(mp[y] < x) mp[y] = x, num[y] = 1;
			else if(mp[y] == x) num[y]++;
		}
		int cnt = 0;
		for(int i = 0 ; i < m; ++i) {
			x = read(), y = read(), z = read();
			if(mp[z]) st[cnt++] = Node(mp[z], x, y, num[z]);
		}
		sort(st, st + cnt);
		int sz = 0;
		for(int i = 1; i < cnt; ++i)
			if(st[sz] == st[i]) st[sz] = st[sz] + st[i];
			else st[++sz] = st[i];
		LL ans = 0;
		for(int i = sz; i >= 0; --i) {
			x = st[i].b, y = st[i].c;
			LL tmp = Que(LIM, LIM) - Que(x - 1, LIM) - Que(LIM, y - 1) + Que(x - 1, y - 1);
			if(!tmp) ans += st[i].sum;
			add(x, y, 1);
		}
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}
