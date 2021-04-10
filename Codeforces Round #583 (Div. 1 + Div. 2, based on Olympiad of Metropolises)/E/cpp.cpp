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
pair<int, int> d[N];
int c[N * 2], len = 0, n;
int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		d[i] = mk(read(), i);
	sort(d + 1, d + n + 1, greater<pair<int, int> >());
	for(int i = 1; i <= n; ++i)
		c[++len] = d[i].r * 2 - 1;
	for(int i = 1; i <= n - 1; ++i)
		printf("%d %d\n", c[i], c[i + 1]);
	for(int i = 1; i <= n; ++i) {
		if(d[i].l == len - i + 1) {
			c[++len] = d[i].r * 2;
			printf("%d %d\n", c[len - 1], c[len]);
		}
		else
			printf("%d %d\n", c[i + d[i].l - 1], d[i].r * 2);
	}
				   
	return 0;
}
