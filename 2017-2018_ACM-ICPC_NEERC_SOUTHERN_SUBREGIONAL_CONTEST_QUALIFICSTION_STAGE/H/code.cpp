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
const int N = 100010;
int n;
LL a[N], b[N], ans;
LL f1[N], s1[N], f2[N], s2[N];

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	//Hzy("H");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), b[n - i + 1] = a[i];
	for(int i = 1; i <= n; ++i) {
		s1[i] = a[i], s2[i] = b[i], f1[i] = f1[i - 1], f2[i] = f2[i - 1];
		if(a[i] <= s1[i - 1]) f1[i] += s1[i - 1] + 1 - a[i], s1[i] = s1[i - 1] + 1;
		if(b[i] <= s2[i - 1]) f2[i] += s2[i - 1] + 1 - b[i], s2[i] = s2[i - 1] + 1;
	}
	ans = inf;
	for(int i = 0; i <= n; ++i) {
		if(s1[i] > s2[n - i]) ans = min(ans, f1[i] + f2[n - i]);
		else ans = min(ans, f1[i] + f2[n - i] + s2[n - i] + 1 - s1[i]);
	}
	printf("%I64d\n", ans);
	return 0;
}
