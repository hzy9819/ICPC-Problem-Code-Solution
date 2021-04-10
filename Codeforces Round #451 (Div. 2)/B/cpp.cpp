#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
LL gcd(LL a, LL b) {
	LL c;
	while(b) {
		c = a % b, a = b, b = c;
	}
	return a;
}
LL exgcd(LL a, LL b, LL & x, LL & y) {
	if(b == 0) { x = 1, y = 0; return a; }
	else {
		LL d = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return d;
	}
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL a, b, c;
int main() {
	Hzy("B");
	c = read(), a = read(), b = read();
	LL r = gcd(a, b), x, y, d, dx, dy;
	if(c % r != 0) {
		puts("NO");
		return 0;
	}
	exgcd(a, b, x, y), d = c / r, dx = b / r, dy = a/ r;
	x *= d, y *= d;
	if(x < 0) {
		LL t = (-x) / dx;
		if(t * dx == -x) x = 0, y -= t * dy;
		else x += (t + 1) * dx, y -= (t + 1) * dy;
	}
	else if(y < 0) {
		LL t = (-y) / dy;
		if(t * dy == -y) y = 0, x -= t * dx;
		else y += (t + 1) * dy, x -= (t + 1) * dx;
	}
	if(x < 0 || y < 0) {
		puts("NO");
		return 0;
	}
	puts("YES");
	printf("%I64d %I64d\n", x, y);
	return 0;
}
