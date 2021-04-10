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
const LL weg = 998244353;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, k;
LL f[N][N + N][2];
int main() {
	Hzy("D");
	n = read(), k = read();
	f[1][1][0] = 2;
	f[1][2][1] = 2;
	for(int i = 2; i <= n; ++i)
		for(int j = 1; j <= k; ++j) {
			f[i][j][0] = (f[i - 1][j][1] * 2 + f[i - 1][j - 1][0] + f[i - 1][j][0]) % weg;
			f[i][j][1] = (f[i - 1][j][1] + f[i - 1][j - 1][0] * 2) % weg;
			if(j >= 2) f[i][j][1] = (f[i][j][1] + f[i - 1][j - 2][1]) % weg;
		}
	cout << (f[n][k][0] + f[n][k][1]) % weg << endl;
	return 0;
}
