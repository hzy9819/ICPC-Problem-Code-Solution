#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, x, y, r1, r2;
int main() {
	n = read(), x = read(), y = read();
	r1 = max(x, y) - 1;
	r2 = max(n - x, n - y);
	if(r1 <= r2) puts("White");
	else puts("Black");
	return 0;
}
