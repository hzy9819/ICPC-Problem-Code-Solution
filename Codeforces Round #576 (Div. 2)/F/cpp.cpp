#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 55;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int f[N][N][N][N];
char s[N][N];
int main() {
	Hzy("F");
	n = read();
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i] + 1);
	for(int l1 = 1; l1 <= n; ++l1)
		for(int l2 = 1; l2 <= n; ++l2)
			for(int i = 1, j = i + l1 - 1; j <= n; ++i, ++j)
				for(int k = 1, p = k + l2 - 1; p <= n; ++k, ++p) {
					if(l1 == 1 && l2 == 1) f[i][j][k][p] = (s[i][k] == '#');
					else f[i][j][k][p] = max(l1, l2);
					for(int q = i; q < j; ++q)
						f[i][j][k][p] = min(f[i][j][k][p], f[i][q][k][p] + f[q + 1][j][k][p]);
					for(int q = k; q < p; ++q)
						f[i][j][k][p] = min(f[i][j][k][p], f[i][j][k][q] + f[i][j][q + 1][p]);
				}
	cout << f[1][n][1][n] << endl;
	return 0;
}
