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
const int N = 510;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, k, a[N];
int t(0);

int main() {
	Hzy("B");
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		if(!t || a[i] > a[t]) t = i;
	}
	for(int i = 1; i < t; ++i) {
		int s = 0;
		for(int j = i + 1; j < t; ++j) {
			if(s >= k) break;
			if(a[i] > a[j]) s++;
			else s = 1, i = j;
		}
		if(s >= k) {
			printf("%I64d\n", a[i]);
			return 0;
		}
	}
	printf("%I64d\n", a[t]);
	return 0;
}
