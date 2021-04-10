#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int x, h, m;
bool check(int t) {
	int p = t % 10; t /= 10;
	return (p == 7) | (t == 7);
}
int main() {
	Hzy("A");
	x = read(), h = read(), m = read();
	for(int ans = 0; ; ++ans) {
		if(check(h) || check(m)) { printf("%d\n", ans); return 0;}
		m -= x;
		if(m < 0) m += 60, h--;
		if(h < 0) h += 24;
	}
	return 0;
}
