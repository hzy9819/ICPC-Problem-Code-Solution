#include <bits/stdc++.h>
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
int n, ans;
void check(int x, int y) {
	int z = x ^ y;
	if(z >= x + y || y >= x + z || x >= y + z || z > x) return ;
	ans++;
}
int main() {
	Hzy("B");
	n = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			check(i, j);
	printf("%d\n", ans / 2);								
	return 0;
}
