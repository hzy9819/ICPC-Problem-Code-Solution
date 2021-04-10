#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, m1, m2, s;
LL a[N], b[N];
int main() {
	Hzy("A");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), s += a[i];
	for(int i = 1; i <= n; ++i) {
		b[i] = read();
		if(b[i] >= m1) m2 = m1, m1 = b[i];
		else if(b[i] > m2) m2 = b[i];
	}
	if(s <= m1 + m2) puts("YES");
	else puts("NO");
	return 0;
}
