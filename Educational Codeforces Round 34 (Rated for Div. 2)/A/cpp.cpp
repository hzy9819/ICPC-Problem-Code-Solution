#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int f[110];
int n;
int main() {
	Hzy("A");
	f[0] = 1;
	int x, y;
	for(int i = 1; i <= 100; ++i) {
		x = i - 3;
		y = i - 7;
		if(x >= 0 && f[x]) f[i] = 1;
		if(y >= 0 && f[y]) f[i] = 1;
	}
	n = read();
	for(int i = 1; i <= n; ++i) {
		x = read();
		if(f[x]) puts("YES");
		else puts("NO");
	}
	return 0;
}
