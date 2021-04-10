#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 1010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], ans[N];
int main() {
	Hzy("E");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i)
		if(a[i] < 0) {
			bool fg = 0;
			for(int j = 1; j < i; ++j)
				if(a[j] == -a[i]) {
					fg = 1;
					a[j] = -N;
					break;
				}
			if(fg) continue;
			for(int j = 1; j < i; ++j)
				if(a[j] == 0 && !ans[j]) {
					fg = 1;
					ans[j] = -a[i];
					break;
				}
			if(!fg) {
				puts("No");
				return 0;
			}
		}
	puts("Yes");
	for(int i = 1; i <= n; ++i)
		if(a[i] == 0) {
			if(ans[i]) printf("%d ", ans[i]);
			else printf("1 ");
		}
	return 0;
}
