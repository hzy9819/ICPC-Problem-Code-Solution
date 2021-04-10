#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 100010;
LL n, m, a, d, ans;
LL t[N], sz(0);
int main() {
	freopen("A.in", "r", stdin), freopen("bf.out", "w", stdout);
	scanf("%lld %lld %lld %lld", &n, &m, &a, &d);
	for(int i = 1; i <= m; ++i) scanf("%lld", t + i);
	for(int i = 1; i <= n; ++i) t[++m] = a * i;
	sort(t + 1, t + m + 1);
	LL now(0);
	for(int i = 1; i <= m; ++i) 
		if(now < t[i]) now = t[i] + d, ans++;
	printf("%lld\n", ans);
	return 0;
}

