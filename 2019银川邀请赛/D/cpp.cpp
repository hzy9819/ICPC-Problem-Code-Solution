#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
int main() {
	int T = read(), tc = 0;	
	while(T--) {
		n = read(), m = read();
		tc++;
		printf("Case #%d: %.6f %.6f\n", tc, n == 1 ? 1 : 0.5, (db) (1.0 + m) / (2 * m));
	}
	return 0;
}
