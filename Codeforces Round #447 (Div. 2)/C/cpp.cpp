#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 4010;
const int S = 1000010;
int a[N], s[N], n, m;
bool b[S], used[S];
int now[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int gcd(int a, int b) {
	if(a < b) swap(a, b);
	int c;
	while(b) c = a % b, a = b, b = c;
	return a;
}
int main() {
	Hzy("C");
	m = read();
	for(int i = 1; i <= m; ++i) s[i] = read();
	int t = s[m];
	for(int i = 1; i < m; ++i) t = gcd(s[i], t);
	if(t != s[1]) {
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= m; ++i) {
		a[++n] = s[i];
		a[++n] = s[1];
	}
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) printf("%d ", a[i]);			
	return 0;
}
