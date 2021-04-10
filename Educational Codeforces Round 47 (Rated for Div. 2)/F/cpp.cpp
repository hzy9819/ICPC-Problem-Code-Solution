#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

const int N = 1000010;
struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int n, fa[N];
void Init() {
	for(int i = 1; i <= n; ++i) fa[i] = 0, lst[i] = -1;
}
void dfs(int t) {
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			fa[e[i].to] = t;
			dfs(e[i].to);
		}
}

vector <int> v[N];
int ans[N];

void Merge(vector <int> & x, vector <int> & y, int & mx) {
	int sz1 = x.size(), sz2 = y.size();
	for(int i = 0; i < sz2; ++i) {
		x[sz1 - 1 - i] += y[sz2 - 1 - i];
		if(x[sz1 - 1 - i] > x[sz1 - 1 - mx] || (i < mx && x[sz1 - 1 - i] == x[sz1 - 1 - mx])) mx = i;
	}
}

void Dfs(int t) {
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t])
			Dfs(e[i].to);
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != fa[t]) {
			if(v[e[i].to].size() > v[t].size())
				swap(v[e[i].to], v[t]), ans[t] = ans[e[i].to];
			Merge(v[t], v[e[i].to], ans[t]) ;
		}
	int tmp = v[t].size();
	ans[t]++;
	if(!tmp || v[t][tmp - ans[t]] <= 1) ans[t] = 0;
	v[t].push_back(1);
}

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("F");
	n = read();
	Init();
	int x, y;
	for(int i = 1; i < n; ++i) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1);
	Dfs(1);
	for(int i = 1; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
