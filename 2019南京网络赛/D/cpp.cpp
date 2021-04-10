#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int din[N], dout[N], dd[N];

queue <int> Q;

db f[N];
int n, m;

int main() {
	int T = read();
	while(T--) {
		n = read(), m = read();
		for(int i = 1; i <= n; ++i)
			din[i] = dout[i] = 0, lst[i] = -1, f[i] = 0.0;
		f[1] = 1.0;
		int u, v;
		for(int i = 1; i <= m; ++i) {
			u = read(), v = read();
			dout[u]++, din[v]++;
			add(u, v);
		}
		for(int i = 1; i <= n; ++i)
			dd[i] = din[i];
		while(!Q.empty())
			Q.pop();
		int t;
		Q.push(1) ;
		while(!Q.empty()) {
			t = Q.front(); Q.pop();
			db q = 1.0 / (dout[t] + 1), tmp;
			tmp = 1.0 / ((1.0 - q) * (1.0 - q));
			for(int i = lst[t]; i >= 0; i = e[i].next) {
				f[e[i].to] += f[t] + tmp * (1 - q) / dout[t];
				din[e[i].to]--;
				if(!din[e[i].to]) {
					Q.push(e[i].to);
				}
			}
		}
		printf("%.2lf\n", f[n]);
	}
	return 0;
}
