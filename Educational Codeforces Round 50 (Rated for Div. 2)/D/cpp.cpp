#include <bits/stdc++.h>
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
int a[N], b[N];
LL s1, s2;
int n, m, ans;
int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), s1 += a[i];
	m = read();
	for(int i = 1; i <= m; ++i) b[i] = read(), s2 += b[i];
	if(s1 != s2) {
		puts("-1");
		return 0;
	}
	LL n1, n2, p;
	n1 = n2 = 0, p = 1;
	for(int i = 1; i <= n; ++i) {
		n1 += a[i];
		while(n2 < n1 && p <= m) n2 += b[p++];
		if(n1 == n2) ans++;
	}
	cout << ans << endl;
	return 0;
}
