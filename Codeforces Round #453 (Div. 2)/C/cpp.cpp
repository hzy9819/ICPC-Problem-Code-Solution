#include <bits/stdc++.h>
#define pb push_back
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
vector <int> dep[N];
int fa1[N], fa2[N];
int n, h[N];
int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n + 1; ++i) h[i] = read();
	dep[1].pb(1);
	fa1[1] = 0;
	int tot = 1, ls = 1;
	for(int i = 2; i <= n + 1; ++i) {
		for(int j = 1; j <= h[i]; ++j) {
			dep[i].pb(++tot);
			fa1[tot] = ls;
		}
		ls = tot;
	}
	for(int i = 1; i <= tot; ++i) fa2[i] = fa1[i];
	bool fg = 0;
	for(int i = n + 1; i >= 2; --i) {
		if(h[i] > 1 && h[i - 1] > 1) {
			fa2[dep[i][0]] = dep[i - 1][0];
			fg = 1;
			break;
		}
	}
	if(!fg) puts("perfect");
	else {
		puts("ambiguous");
		for(int i = 1; i <= tot; ++i)
			printf("%d ", fa1[i]);
		puts("");
		for(int i = 1; i <= tot; ++i)
			printf("%d ", fa2[i]);
	}
	return 0;
}
