#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 210;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N];
int main() {
	int T = read();
	while(T--) {
		n = read();
		for(int i = 1; i <= n; ++i)
			a[i] = read();
		bool fg = 1;
		for(int i = 1; i < n; ++i)
			if(abs(a[i] - a[i + 1]) != 1 && (a[i] + a[i + 1] != n + 1 || abs(a[i] - a[i + 1]) != n - 1)) {
				fg = 0;
				break;
			}
		fg ? puts("YES") : puts("NO");
	}
	return 0;
}
