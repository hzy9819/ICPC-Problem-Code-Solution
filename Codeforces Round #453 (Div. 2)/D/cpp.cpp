#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 155;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], b[N], c[N], ans1[N], ans2[N], p[N], pp[N];
bool flag(0);
void work(int t, int *a, int *b, int *c) {
	if(t == n) {
		if(a[n] < 0 && b[n - 1] < 0)
			for(int i = 0; i <= n; ++i) a[i] = -a[i], b[i] = -b[i];
		if(a[n] + b[n - 1] == 0) return ;
		flag = 1;
		for(int i = 0; i <= n; ++i)
			ans1[i] = a[i], ans2[i] = b[i];
		return ;
	}
	bool fg = 0;
	int r[t + 1], rr[t + 2];
	for(int i = 0; i <= t + 1; ++i) {
		p[i] = b[i] + (i == 0 ? 0 : a[i - 1]);
		if(p[i] > 1 || p[i] < -1) {
			fg = 1;
			break;
		}
	}
	if(!fg) {
		for(int i = 0; i <= t + 1; ++i) c[i] = p[i];
		for(int i = 0; i <= t; ++i) r[i] = a[i], rr[i] = b[i];
		work(t + 1, c, a, b);
		for(int i = 0; i <= t; ++i) a[i] = r[i], b[i] = rr[i];
		if(!flag) fg = 1;
	}
	if(fg) {
		fg = 0;
		for(int i = 0; i <= t + 1; ++i) {
			p[i] = b[i] - (i == 0 ? 0 : a[i - 1]);
			if(p[i] > 1 || p[i] < -1) {
				fg = 1;
				break;
			}
		}
		if(!fg) {
			for(int i = 0; i <= t + 1; ++i) c[i] = p[i];
			for(int i = 0; i <= t; ++i) r[i] = a[i], rr[i] = b[i];
			work(t + 1, c, a, b);
			for(int i = 0; i <= t; ++i) a[i] = r[i], b[i] = rr[i];
		}
	}
}
void clear() {
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);
	memset(c, 0, sizeof c);
}
int main() {
	Hzy("D");
	for(int i = 1; i <= 150; ++i) {
		n = i, flag = 0;
		clear();
		a[0] = 1, b[1] = 1;
		work(1, b, a, c);
		if(!flag) {
			clear();
			a[0] = 1;
			b[1] = 1, b[0] = -1;
			work(1, b, a, c);
		}
		if(!flag) {
			clear();
			a[0] = 1;
			b[1] = -1, b[0] = 0;
			work(1, b, a, c);
		}
		if(!flag) {
			clear();
			a[0] = 1;
			b[1] = -1, b[0] = -1;
			work(1, b, a, c);
		}
		if(!flag) {
			clear();
			a[0] = 1;
			b[1] = 1, b[0] = 1;
			work(1, b, a, c);
		}
		/*if(flag) {
			printf("%d\n", n);
			for(int i = 0; i <= n; ++i)
				printf("%d ", ans1[i]);
			puts("");
			printf("%d\n", n - 1);
			for(int i = 0; i < n; ++i)
				printf("%d ", ans2[i]);
		}
		else puts("-1");*/
		if(!flag) printf("%d\n", i);
		}
	return 0;
}
