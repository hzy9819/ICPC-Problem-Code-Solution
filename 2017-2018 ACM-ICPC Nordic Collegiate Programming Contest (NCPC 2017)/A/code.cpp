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
const int N = 500010;
struct Node {
	int d; db ans;
	bool operator < (const Node & p) const {
		return p.ans < ans;
	}
	Node (int _d, db _ans) : d(_d), ans(_ans) {}
};
priority_queue <Node> Q1, Q2, Q3;
db lm;
LL l, a, b, t, r, lm1, lm2;
LL n, d[N], s[N];
int p1(1), p2(1), pre[N], sz, ans[N];
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
db f[N];
void add1(int x) {
	Q1.push(Node(x, f[x] - (db) d[x] / a));
}
void add2(int x) {
	Q2.push(Node(x, f[x] - (db) d[x] / b));
}
void add3(int x) {
	Q3.push(Node(x, f[x] - (db) d[x] / a));
}
int main() {
	Hzy("A");
	l = read(), a = read(), b = read(), t = read(), r = read();
	n = read(); lm1 = a * t, lm2 = lm1 + b * r;
	for(int i = 1; i <= n; ++i) d[i] = read();
	d[++n] = l;
	db t1, t2, t3;
	int tp1, tp2, tp3;
	//Q1.push(Node(0, 0.0));
	for(int i = 1; i <= n; ++i) {
		lm = d[i], lm /= a, f[i] = lm;
		
		while(d[i] - d[p1] > lm1)
			add2(p1), p1++;
		while(!Q1.empty() && Q1.top().d < p1)
			Q1.pop();
		if(Q1.empty())
			tp1 = 0, t1 = lm;
		else
			tp1 = Q1.top().d, t1 = f[tp1] + (db) (d[i] - d[tp1]) / a;

		while(d[i] - d[p2] > lm2)
			add3(p2), p2++;
		while(!Q2.empty() && Q2.top().d < p2)
			Q2.pop();
		if(Q2.empty())
			tp2 = 0, t2 = lm;
		else
			tp2 = Q2.top().d, t2 = f[tp2] + (db) (d[i] - d[tp2] - lm1) / b + t;

		if(Q3.empty())
			tp3 = 0, t3 = lm;
		else
			tp3 = Q3.top().d, t3 = f[tp3] + (db) (d[i] - d[tp3] - lm2) / a + t + r;

		if(t1 < f[i]) f[i] = t1, pre[i] = tp1;
		if(t2 < f[i]) f[i] = t2, pre[i] = tp2;
		if(t3 < f[i]) f[i] = t3, pre[i] = tp3;

		add1(i);
	}
	int now = pre[n];
	while(now) {
		ans[++sz] = now - 1;
		now = pre[now];
	}
	printf("%d\n", sz);
	for(int i = sz; i >= 1; --i) printf("%d ", ans[i]);
	return 0;
}
