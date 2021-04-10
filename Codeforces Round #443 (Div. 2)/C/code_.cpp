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

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	freopen("data.out", "w", stdout);
	int x, y;
	for(int i = 0; i <= 1023; ++i) {
		x = y = i;
		x |= 999, x ^= 689;
		y &= 350, y |= 326, y ^= 16;
		if(x != y) printf("%d %d %d\n", i, x, y);
	}
	return 0;
}
