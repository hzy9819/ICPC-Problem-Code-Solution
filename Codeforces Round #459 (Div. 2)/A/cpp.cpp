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
int n;
int f[1010];
bool b[10010];
int main() {
	Hzy("A");
	n = read();
	f[1] = 1, f[2] = 2;
	b[1] = 1, b[2] = 1;
	for(int i = 3; ; ++i) {
		f[i] = f[i - 1] + f[i - 2];
		b[f[i]] = 1;
		if(f[i] >= n) break;
	}
	for(int i = 1; i <= n; ++i)
		if(b[i]) printf("O");
		else printf("o");
	return 0;
}
