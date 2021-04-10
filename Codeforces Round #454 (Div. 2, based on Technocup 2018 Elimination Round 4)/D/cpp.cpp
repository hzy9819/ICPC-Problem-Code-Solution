#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int n, m, to[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("D");
	n = read(), m = read();
	if(n == 1 && m == 1) {
		puts("YES");
		puts("1");
		return 0;
	}
	if(max(n, m) <= 2) {
		puts("NO");
		return 0;
	}
	if(n != m && max(n, m) <= 3) {
		puts("NO");
		return 0;
	}
	//int a[n + 1][m + 1];
	puts("YES");
	if(n == 3 && m == 3) {
		puts("6 7 2");
		puts("1 5 9");
		puts("8 3 4");
		return 0;
	}
	bool fg = 0;
	int cnt;
	if(n > m) swap(n, m), fg = 1;
	int a[n + 1][m + 1];
	if(n == 2 && m == 4) {
		a[1][1] = 5, a[1][2] = 4, a[1][3] = 7, a[1][4] = 2;
		a[2][1] = 3, a[2][2] = 6, a[2][3] = 1, a[2][4] = 8;
	}
	else if(n == 3 && m == 4) {
		a[1][1] = 10, a[1][2] = 12, a[1][3] = 9, a[1][4] = 11;
		a[2][1] = 5, a[2][2] = 4, a[2][3] = 7, a[2][4] = 2;
		a[3][1] = 3, a[3][2] = 6, a[3][3] = 1, a[3][4] = 8;
	}
	else if(n == 4 && m == 4) {
		a[1][1] = 11, a[1][2] = 16, a[1][3] = 9, a[1][4] = 14;
		a[2][1] = 13, a[2][2] = 10, a[2][3] = 15, a[2][4] = 12;
		a[3][1] = 5, a[3][2] = 4, a[3][3] = 7, a[3][4] = 2;
		a[4][1] = 3, a[4][2] = 6, a[4][3] = 1, a[4][4] = 8;
	}
	else if(m & 1) {
		for(int i = 1; i <= n; ++i)
			if(i & 1) {
				cnt = 0;
				for(int j = 1; 2 * j - 1 <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j - 1;
				for(int j = 1; 2 * j <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j;
			}
			else {
				cnt = 0;
				for(int j = 2; 2 * j - 1 <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j - 1;
				a[i][++cnt] = (i - 1) * m + 1;
				for(int j = 2; 2 * j <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j;
				a[i][++cnt] = (i - 1) * m + 2;
			}
	}
	else {
		for(int i = 1; i <= n; ++i) {
			if(i & 1) {
				cnt = 0;
				for(int j = 1; 2 * j <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j;
				for(int j = 1; 2 * j - 1 <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j - 1;
			}
			else {
				cnt = 0;
				for(int j = 1; 2 * j - 1 <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j - 1;
				for(int j = 1; 2 * j <= m; ++j)
					a[i][++cnt] = (i - 1) * m + 2 * j;
			}
		}
	}
	if(fg) {
		cnt = 0;
		for(int i = 1; i <= m; ++i)
			for(int j = 1; j <= n; ++j)
				to[(j - 1) * m + i] = ++cnt;
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j) {
				//x = (a[j][i] / m) * n + (
				printf("%d ", to[a[j][i]]);
			}
			puts("");
		}
	}
	else
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= m; ++j)
				printf("%d ", a[i][j]);
			puts("");
		}				
	return 0;
}
