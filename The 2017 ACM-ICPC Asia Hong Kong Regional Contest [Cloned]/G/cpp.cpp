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
const int V = 2010;
const int N = 10010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int v, n;
int a[N], f[V], pre[V], sum[N];

int main() {
	Hzy("G");
	while(cin >> v) {
		for(int i = 1; i <= v; ++i) f[i] = -1, pre[i] = 0;
		n = read();
		for(int i = 1; i <= n; ++i)
			a[i] = read(), f[a[i]] = 1, sum[i] = 0, pre[a[i]] = i;
		int r = n;
		for(int i = 1; i < v; ++i) {
			if(f[i] == -1) continue;
			while(r && i + a[r] > v) r--;
			for(int j = 1; j <= r; ++j)
				if(f[i + a[j]] == -1 || f[i] + 1 <= f[i + a[j]]) {
					pre[i + a[j]] = j;
					f[i + a[j]] = f[i] + 1;
				}
		}
		if(f[v] == -1) {
			puts("-1");
			continue;
		}
		int now = v;
		while(now)
			sum[pre[now]]++, now -= a[pre[now]];
		for(int i = 1; i <= n; ++i)
			printf("%d ", sum[i]);
		puts("");
	}		
	return 0;
}
