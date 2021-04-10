#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
int n = 100000, m = 100000;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	freopen("E.in", "w", stdout);
	srand(time(0));
	printf("%d %d\n", n, m);
	for(int i = 1; i <= m; ++i)
		printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10 + 1);
	puts("1");
	return 0;
}
