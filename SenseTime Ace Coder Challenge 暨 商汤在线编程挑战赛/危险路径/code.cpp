#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <time.h>
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
	freopen("G.in", "w", stdout);
	int addr;
	srand(time(0) + (unsigned long long)(&addr));
	int n, m;
	puts("10");
	for(int i = 1; i <= 10; ++i) {
		n = rand() % 100 + 1, m = rand() % 200 + n - 1;
		printf("%d %d\n", n, m);
		for(int j = 1; j < n; ++j) 
			printf("%d %d %d\n", j, j + 1, rand() % 1000000001);
		for(int j = n; j <= m; ++j)
			printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000000001);
	}
	return 0;
}
