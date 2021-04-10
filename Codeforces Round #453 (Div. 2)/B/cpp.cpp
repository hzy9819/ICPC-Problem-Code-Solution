#include <bits/stdc++.h>
#define LL long long
#define db double
#define pb push_back
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, a[N], b[N], l, r;
vector <int> add[N];
int c[N], bc[N], tot;
void dfs(int t, int lc) {
	if(lc != c[t]) {
		tot++;
		bc[t] = c[t];
		lc = c[t];
	}
	else
		bc[t] = lc;
	for(int i = 0; i < add[t].size(); ++i)
		dfs(add[t][i], lc);
}
void solve() {
	n = read();
	for(int i = 2; i <= n; ++i) {
		int x = read();
		add[x].pb(i);
	}
	for(int i = 1; i <= n; ++i)
		c[i] = read();
	dfs(1, 0);
	printf("%d\n", tot);
}
int main() {
	Hzy("B");
	solve();
	return 0;
}
