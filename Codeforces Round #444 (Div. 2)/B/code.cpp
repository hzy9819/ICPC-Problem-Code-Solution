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

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
bool b[5][10], u[5];
bool check(int t) {
	if(!t) return 1;
	bool tmp = 0;
	for(int i = 1; i <= n; ++i) if(!u[i] && b[i][t % 10]) {
			u[i] = 1;
			tmp = check(t / 10);
			u[i] = 0;
			if(tmp) return 1;
		}
	return 0;
}
int main() {
	Hzy("B");
	n = read();
	int t;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= 6; ++j) t = read(), b[i][t] = 1;
	for(int i = 1; ; ++i) if(!check(i)) {
			printf("%d", i - 1);
			break;
		}
	return 0;
}
