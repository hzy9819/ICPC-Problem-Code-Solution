#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
LL n, q;
LL calc(LL x, LL y) {
	if((x + y) & 1) return (n * n + 1) / 2 + (x / 2) * (n / 2) + ((x - 1) / 2) * ((n + 1) / 2) + (y + 1) / 2;
	else return (x / 2) * ((n + 1) / 2) + ((x - 1) / 2) * (n / 2) + (y + 1) / 2;
}
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("B");
	n = read(), q = read();
	LL x, y;
	for(int i = 1; i <= q; ++i) {
		x = read(), y = read();
		cout << calc(x, y) << endl;
	}
	return 0;
}
