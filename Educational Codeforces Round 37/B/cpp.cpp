#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
int t, n, l, r, cnt;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("B");
	t = read();
	while(t--) {
		n = read();
		cnt = 1;
		for(int i = 1; i <= n; ++i) {
			l = read(), r = read();
			if(cnt > r) {
				printf("0 ");
				continue;
			}
			if(l > cnt) cnt = l;
			printf("%d ", cnt++);
		}
		puts("");
	}			
	return 0;
}
