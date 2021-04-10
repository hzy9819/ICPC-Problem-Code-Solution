#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
LL a, b, x, y, z, na, nb;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("A");
	a = read(), b = read(), x = read(), y = read(), z = read();
	//nd = x * 2 + y * 2 + z * 3;
	na = x * 2 + y;
	nb = y + z * 3;
	printf("%lld\n", ((na - a) >= 0 ? na - a : 0) + ((nb - b) >= 0 ? nb - b : 0));
	return 0;
}
