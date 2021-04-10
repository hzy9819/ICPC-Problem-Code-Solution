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

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, k;

void Dfs(int t) {
	while(n && t <= k) {
		n--, k -= t, putchar('(');
		Dfs(t + 1);
		putchar(')');
	}
}
int main() {
	//Hzy("C");
	n = read(), k = read();
	if(k > n * (n - 1) / 2) {
		puts("Impossible");
		return 0;
	}
	Dfs(0);
	return 0;
}
