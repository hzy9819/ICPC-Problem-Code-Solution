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

int n, a, b, c, ans;

int main() {
	//Hzy("A");
	n = read(), a = read(), b = read(), c = read();
	if(n <= 1) {puts("0"); return 0;}
	n--;
	int t = min(min(a, b), c);
	if(t == c) ans = min(a, b) + (n - 1) * c;
	else ans = n * t;
	printf("%d\n", ans);
	return 0;
}
