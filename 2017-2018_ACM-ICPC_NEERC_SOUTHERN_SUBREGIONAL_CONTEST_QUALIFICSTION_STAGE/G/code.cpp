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
const int N = 1010;
int n, ans;
bool b[N][7];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	//Hzy("G");
	n = read();
	char c[10];
	for(int i = 1; i <= n; ++i) {
		scanf("%s", c);
		for(int j = 0; j < 7; ++j) b[i][j] = c[j] - '0';
	}
	ans = 0;
	for(int i = 0; i < 7; ++i) {
		int tmp = 0;
		for(int j = 1; j <= n; ++j) if(b[j][i]) tmp++;
		ans = max(ans, tmp);
	}
	printf("%d", ans);
	return 0;
}
