#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define mk make_pair
#define fr first
#define se second
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 500010;
int fa[N], pre_fa[N], now[N];
int n, m, q, cnt, lim;
struct Edge {
	int u, v, w;
}e[N];
vector<pair<int, int> > v[N];
vector<int> w[N];
bool b[N];
int find_fa1(int t) {
	if(pre_fa[t] != t) pre_fa[t] = find_fa1(pre_fa[t]);
	return pre_fa[t];
}

int find_fa2(int t) {
	if(now[t] != cnt) {now[t] = cnt, fa[t] = pre_fa[t];}
	if(fa[t] != t) fa[t] = find_fa2(fa[t]);
	return fa[t];
}

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("E");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) fa[i] = pre_fa[i] = i;
	for(int i = 1; i <= m; ++i) {
		e[i].u = read(), e[i].v = read(), e[i].w = read(), lim = max(lim, e[i].w);
		w[e[i].w].push_back(i);
	}
	q = read();
	int s, x, y;
	for(int i = 1; i <= q; ++i) {
		s = read();
		for(int j = 1; j <= s; ++j) {
			x = read();
			v[e[x].w].push_back(mk(i, x));
		}
	}
	for(int i = 1; i <= lim; ++i) {
		//sort(v[i].begin(), v[i].end());
		for(int j = 0; j < v[i].size(); ++j) {
			if(j == 0 || v[i][j].fr != v[i][j - 1].fr) cnt++;
			s = v[i][j].se;
			x = e[s].u, y = e[s].v;
			x = find_fa2(x), y = find_fa2(y);
			if(x == y) b[v[i][j].fr] = 1;
			else fa[x] = y;
		}
		for(int j = 0; j < w[i].size(); ++j) {
			s = w[i][j];
			x = e[s].u, y = e[s].v;
			x = find_fa1(x), y = find_fa1(y);
			if(x != y) pre_fa[x] = y;
		}		
	}
	for(int i = 1; i <= q; ++i)
		b[i] ? puts("NO") : puts("YES");
	return 0;
}
