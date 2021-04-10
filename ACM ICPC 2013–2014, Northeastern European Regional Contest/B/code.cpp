#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 3010;
db f[N][N];

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, a, b;
int main() {
	Hzy("bonus");
	n = read(), a = read(), b = read();
	//a++;
	db tmp;
	for(int i = n; i >= 0; --i)
		for(int j = min(a, i); j >= max(0, i - b); --j) {
			tmp = 2.0 / (2.0 + 2.0 * (a - j) + (b - i + j));
			//f[i][j] = tmp * (a - j) * f[i + 1][j + 1] + tmp * 0.5 * (b - i + j + 1) * f[i + 1][j];
			f[i][j] = tmp * (1 - f[i + 1][j + 1] + 1 - f[i + 1][j]);
			//f[i][j] = (2.0 + 2.0 * (a - j) * f[i + 1][j + 1] + (db) (b - i + j) * f[i + 1][j]) / (2.0 + 2.0 * (a - j) + (b - i + j));
		}
						 
	printf("%.16lf\n", f[0][0]);
	memset(f, 0, sizeof f);
	//a--, b++;
	for(int i = n; i >= 0; --i)
		for(int j = min(a, i); j >= max(0, i - b); --j)
			f[i][j] = (1.0 + 2.0 * (a - j) * f[i + 1][j + 1] + (db) (b - i + j) * f[i + 1][j]) / (1.0 + 2.0 * (a - j) + (b - i + j));
	printf("%.16lf\n", f[0][0]);
	return 0;
}
