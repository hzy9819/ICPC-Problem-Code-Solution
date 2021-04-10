#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int n, m;
vector <int> v[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int st[N], sz, ans[N], fa[N];
void impos() {
	puts("No");
	exit(0);
}
int find_fa(int x) {
	if(x != fa[x]) fa[x] = find_fa(fa[x]);
	return fa[x];
}
void add(int x, int y) {
	x = find_fa(x), y = find_fa(y);
	if(x > y) swap(x, y);
	if(x == (100000 + 1) && y == (100000 + 2)) impos();
	fa[x] = y;
}

int main() {
	//Hzy("E");
	n = read(), m = read();
	for(int i = 1; i <= 100000 + 2; ++i) fa[i] = i;
	for(int i = 1; i <= n; ++i) {
		int x = read();
		for(int j = 1; j <= x; ++j) v[i].push_back(read());
	}
	for(int i = n - 1; i >= 1; --i) {
		int x1 = v[i].size(), x2 = v[i + 1].size(), t1, t2;
		bool fg(0);
		for(int j = 0; j < min(x1, x2); ++j) {
			t1 = v[i][j], t2 = v[i + 1][j];
			if(t1 == t2) continue;
			fg = 1;
			if(t1 < t2) add(t1, t2);
			else add(t1, 100000 + 1), add(t2, 100000 + 2);
			break;
		}
		if(fg) continue;
		else if(x1 > x2) impos();
	}
	for(int i = 1; i <= 100000; ++i) {
		int x = find_fa(i);
		if(x == (100000 + 1)) ans[++sz] = i;
	}
	puts("Yes");
	printf("%d\n", sz);
	for(int i = 1; i <= sz; ++i) printf("%d ", ans[i]);
	return 0;
}
