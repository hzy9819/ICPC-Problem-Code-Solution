#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, ans;
int a[N], b[N];

int main() {
	Hzy("A");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int j = 1; j <= m; ++j) b[j] = read();
	int p = 1;
	for(int i = 1; i <= n; ++i)
		if(b[p] >= a[i]) {
			ans++;
			p++;
			if(p > m) break;
		}
	cout << ans << endl;
	return 0;
}
