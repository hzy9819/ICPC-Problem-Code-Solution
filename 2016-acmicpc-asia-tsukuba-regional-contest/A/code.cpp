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
const int N = 200010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, m;
bool b[N];
int a[N];

int main() {
	Hzy("A");
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) a[i] = read();
	for(int i = m; i >= 1; --i)
		if(!b[a[i]]) {
			printf("%d\n", a[i]);
			b[a[i]] = 1;
		}
	for(int i = 1; i <= n; ++i)
		if(!b[i])
			printf("%d\n", i);
	return 0;
}
