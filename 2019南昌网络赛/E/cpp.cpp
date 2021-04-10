#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 40000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int ans[N], nxt[N];
int n, m, q;
int main() {
	int T = read();
	while(T--) {
		n = read(), m = read() + 1;

		for(int i = 1; i <= n; ++i)
			nxt[i] = i + 1;
		nxt[n] = 1;
		int now = 1, pre = n;
		for(int i = 1; i <= n; ++i) {
			ans[now] = i;
			nxt[pre] = nxt[now];
			for(int j = 0; j < m; ++j) {
				pre = now;
				now = nxt[now];
			}
		}
		
		q = read();
		for(int i = 1; i <= q; ++i)
			printf("%d\n", ans[read()]);
	}
	return 0;
}
