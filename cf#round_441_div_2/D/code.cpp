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
const int N = 300010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, a[N], t[N * 2], ans, po;

void Modify(int x) {for(; x > 0; x -= (x & (-x))) t[x]++;}
int Que(int x) {
	int res(0);
	for(; x <= n; x += (x & (-x))) res += t[x];
	return res;
}

int main() {
	//Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	printf("1 ");
	ans = 1, po = n;
	for(int i = 1; i <= n; ++i) {
		Modify(a[i]), ans++;
		while(po && Que(po) == n - po + 1) po--, ans--;
		printf("%d ", ans);
	}
	return 0;
}
