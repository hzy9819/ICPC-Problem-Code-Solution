#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
int n, T, C, a[N];
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	T = read();
	for(int cas = 1; cas <= T; ++cas) {
		n = read(), C = read() + 1;
		if(C > n * (n + 1) / 2 || C < n) {
			printf("Case #%d: IMPOSSIBLE\n", cas);
			continue;
		}
		int l = 1, r = n, rev = 1, now = 1;
		while(now <= n && (n - now + 1) + (n - now) <= C) {
			C -= n - now + 1;
			if(rev)
				a[r] = now, r--;
			else
				a[l] = now, l++;
			rev ^=1, now++;
		}
		if(C) {
			C -= (n - now + 1);
			if(!rev) {
				for(int i = r - C; i <= r; ++i)
					a[i] = now++;
				for(int i = r - C - 1; i >= l; --i)
					a[i] = now++;
			}
			else {
				for(int i = l + C; i >= l; --i)
					a[i] = now++;
				for(int i = l + C + 1; i <= r; ++i)
					a[i] = now++;
			}
		}
		printf("Case #%d: ", cas);
		for(int i = 1; i <= n; ++i)
			printf("%d ", a[i]);
		puts("");
	}
	return 0;
}
