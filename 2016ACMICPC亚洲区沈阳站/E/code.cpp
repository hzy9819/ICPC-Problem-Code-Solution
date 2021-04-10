#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define LL long long
#define db double
#define mk make_pair
#define fi first
#define se second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 110;
const int M = 1010;
pair <LL, LL> s[N];
bool b[N];
LL bin[65];
int dg[N], ans;
struct Edge {
	int to, next;
}e[M * 2];
int list[N], d;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, S;
void add(int x, int y) {
	if(y > 60) s[x].se |= bin[y - 60];
	else s[x].fi |= bin[y];
	e[d].to = y, e[d].next = list[x], list[x] = d++;
}
priority_queue < pair<int, int> > Q;
bool can(pair <LL, LL> st, int t) {
	if((st.fi & s[t].fi) == st.fi && (st.se & s[t].se) == st.se) return 1;
	return 0;
}
inline void dfs(int t, pair <LL, LL> st, int num, int pre) {
	if(num >= S) {ans++; return ;}
	for(int i = pre; i >= 0; i = e[i].next) if(b[e[i].to] && can(st, e[i].to)) {
			if(e[i].to <= 60) st.fi |= bin[e[i].to];
			else st.se |= bin[e[i].to - 60];
			dfs(t, st, num + 1, i);
			if(e[i].to <= 60) st.fi ^= bin[e[i].to];
			else st.se ^= bin[e[i].to - 60];
		}
}
void work(int t) {
	pair <LL, LL> st;
	st.fi = st.se = 0;
	if(t > 60) st.se |= bin[t - 60];
	else st.fi |= bin[t];
	dfs(t, st, 1, list[t]);
}
int main() {
	Hzy("E");
	int T = read(), x, y;
	pair <int, int> t;
	bin[1] = 1;
	for(int i = 2; i <= 60; ++i) bin[i] = bin[i - 1] << 1;
	while(T--) {
		n = read(), m = read(), S = read();
		d = 0; memset(list, -1, sizeof list);
		while(!Q.empty()) Q.pop(); ans = 0;
		for(int i = 1; i <= n; ++i) 
			s[i].fi = s[i].se = 0, b[i] = 1, dg[i] = 0;
		for(int i = 1; i <= m; ++i) {
			x = read(), y = read();
			add(x, y), add(y, x);
		}
		for(int i = 1; i <= n; ++i) {
			x = 0;
			for(int j = 1; j <= 60; ++j) if(s[i].fi & bin[j]) x++;
			for(int j = 61; j <= n; ++j) if(s[i].se & bin[j - 60]) x++;
			dg[i] = x;
			Q.push(mk(-x, i));
		}
		while(!Q.empty()) {
			t = Q.top(), Q.pop();
			if(-t.fi < S - 1 || !b[t.se]) continue;
			work(t.se);
			for(int j = 1; j <= 60; ++j) if(s[t.se].fi & bin[j]) {
					dg[j]--;
					if(dg[j] >= S - 1) Q.push(mk(-dg[j], j));
				}
			for(int j = 61; j <= n; ++j) if(s[t.se].se & bin[j - 60]) {
					dg[j]--;
					if(dg[j] >= S - 1) Q.push(mk(-dg[j], j));
				}
			b[t.se] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
