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
const LL weg = 2147493647LL;
struct Mat {
	int n, m;
	LL f[8][8];
};
LL c[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0, 0},
	{0, 2, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0, 0, 0, 0},
	{0, 4, 0, 4, 1, 0, 0, 0},
	{0, 6, 0, 6, 3, 1, 0, 0},
	{0, 4, 0, 4, 3, 2, 1, 0},
	{0, 1, 0, 1, 1, 1, 1, 1}
};
void operator *= (Mat & a, Mat b) {
	int n = a.n, m = b.m, t = a.m;
	LL tp;
	Mat c;
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			tp = 0;
			for(int k = 1; k <= t; ++k) {
				tp += a.f[i][k] * b.f[k][j] % weg;
				if(tp >= weg) tp -= weg;
			}
			c.f[i][j] = tp;
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a.f[i][j] = c.f[i][j];
	a.n = n, a.m = m;
}

void operator ^= (Mat & a, LL k) {
	Mat b;
	int n = a.n;
	b.n = b.m = n;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			b.f[i][j] = (i == j);
	while(k) {
		if(k & 1) b *= a;
		a *= a;
		k >>= 1;
	}
	a = b;
}
	
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
Mat s, t;
LL n, a, b;
void Init() {
	s.n = 1, s.m = 7;
	s.f[1][1] = b, s.f[1][2] = a, s.f[1][3] = 16, s.f[1][4] = 8, s.f[1][5] = 4, s.f[1][6] = 2, s.f[1][7] = 1;
	t.n = t.m = 7;
	for(int i = 1; i <= 7; ++i)
		for(int j = 1; j <= 7; ++j)
			t.f[i][j] = c[i][j];
}
void work() {
	if(n <= 2) {
		if(n == 1) printf("%lld\n", a);
		else printf("%lld\n", b);
		return ;
	}
	t ^= (n - 2);
	s *= t;
	printf("%lld\n", s.f[1][1]);
}

int main() {
	Hzy("C");
	int T = read();
	while(T--) {
		n = read(), a = read(), b = read();
		Init();
		work();
	}
	return 0;
}
