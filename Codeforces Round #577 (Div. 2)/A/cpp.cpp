#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, a[N], num[N][5], ans = 0;
char s[N][N];
int main() {
	Hzy("A");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i]);
	for(int i = 0; i < m; ++i)
		a[i] = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < m; ++j)
			num[j][ s[i][j] - 'A' ]++;
	for(int i = 0; i < m; ++i) {
		int tmp = max(num[i][0], max(num[i][1], max(num[i][2], max(num[i][3], num[i][4]))));
		ans += tmp * a[i];
	}
	cout << ans << endl;
	return 0;
}
