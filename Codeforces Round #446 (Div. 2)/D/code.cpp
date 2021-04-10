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
const int N = 25;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
struct Data {
	int pos, s;
}a[N];
bool cmp(const Data & x, const Data & y) {return x.s < y.s;}
int ans[N];
int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) a[i].s = read(), a[i].pos = i;
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; ++i) {
		if(i == 1) ans[a[i].pos] = a[n].s;
		else ans[a[i].pos] = a[i - 1].s;
	}
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}
