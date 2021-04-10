#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100100;
bool b[N];
int p[N], sz;
int n, m;
void Prime() {
	for(int i = 2; i <= 100050; ++i) {
		if(!b[i]) p[++sz] = i;
		for(int j = 1; j <= sz && i * p[j] <= 100050; ++j) {
			b[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int ans, s[N];
int main() {
	Hzy("C");
	Prime();
	n = read(), m = read();
	for(int i = 1; i <= sz; ++i)
		if(p[i] >= (n - 1)) {
			ans = p[i];
			break;
		}
	for(int i = 1; i < n; ++i) s[i] = 1;
	for(int i = 1; i <= (ans - n + 1); ++i) s[i]++;
	printf("%d %d\n", ans, ans);
	m -= (n - 1);
	for(int i = 1; i < n; ++i)
		printf("%d %d %d\n", i, i + 1, s[i]);
	for(int i = 1; i <= n; ++i) {
		if(!m) break;
		for(int j = i + 2; j <= n; ++j) {
			if(!m) break;
			printf("%d %d %d\n", i, j, ans + 1);
			m--;
		}
	}
	return 0;
}
