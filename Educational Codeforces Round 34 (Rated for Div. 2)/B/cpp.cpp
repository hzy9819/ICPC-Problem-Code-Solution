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
int h1, a1, c1, h2, a2, hp, n = 0, ans[1000010];
int main() {
	Hzy("B");
	h1 = read(), a1 = read(), c1 = read(), h2 = read(), a2 = read();
	hp = h1;
	while(h2 > 0) {
		n++;
		if(hp > a2 || h2 - a1 <= 0) {
			ans[n] = 1;
			//puts("STRIKE");
			h2 -= a1, hp -= a2;
		}
		else {
			ans[n] = 0;
			//puts("HEAL");
			hp = hp + c1;
			hp -= a2;
		}
	}
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i)
		if(ans[i]) puts("STRIKE");
		else puts("HEAL");
	return 0;
}
