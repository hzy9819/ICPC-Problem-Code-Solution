#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, a[N];
int main() {
	int T = read();
	while(T--) {
		n = read();
		for(int i = 0; i < 4 * n; ++i)
			a[i] = read();
		sort(a, a + 4 * n);
		bool fg = 0;
		int r = 4 * n - 1;
		for(int i = 0; i < 2 * n; i += 2)
			if(a[i] != a[i + 1] || a[r - i] != a[r - i - 1])
				fg = 1;
		if(n > 1) {
			int s = a[0] * a[r];
			for(int i = 2; i < 2 * n; i += 2)
				if(a[i] * a[r - i] != s)
					fg = 1;
		}
		fg ? puts("NO") : puts("YES");
	}
	return 0;
}
