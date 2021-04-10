#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
int n;
LL S;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}


int main() {
	Hzy("B");
	n = read();
	if(n == 1) {
		puts("No");
		return 0;
	}
	for(int i = 1; i <= n; ++i) S += i;
	int t = sqrt(S);
	for(int i = 2; i <= t; ++i)
		if(S % i == 0) {
			puts("Yes");
			printf("1 %d\n", i);
			printf("%d ", n - 1);
			for(int j = 1; j <= n; ++j)
				if(i != j)
					printf("%d ", j);
			puts("");
			return 0;
		}
	puts("No");
	return 0;
}
