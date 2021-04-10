#include <bits/stdc++.h>
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
int n, a[N], l[N], r[N];
bool b[N];
char s[N];
int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	scanf("%s", s + 1);
	for(int i = 1; i <= n - 1; ++i) b[i] = s[i] - '0';
	int cnt = 1;
	for(int i = 1; i <= n; ++i) {
		l[i] = cnt;
		if(!b[i]) cnt = i + 1;
	}
	cnt = n;
	r[n] = n;
	for(int i = n - 1; i >= 1; --i) {
		if(b[i]) r[i] = r[i + 1];
		else r[i] = i;
	}
	for(int i = 1; i <= n; ++i)
		if(a[i] < l[i] || a[i] > r[i]) {
			puts("NO");
			exit(0);
		}
	puts("YES");
	return 0;
}
