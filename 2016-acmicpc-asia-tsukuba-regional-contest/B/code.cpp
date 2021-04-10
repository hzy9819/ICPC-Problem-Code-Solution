#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define Num(a, b, c, d) ((a * 1000) + (b * 100) + (c * 10) + d)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 10010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int f[15][15];
int num[N], ans;
int calc(int a, int b, int c, int d) {
	int now = 0;
	now = f[now][a];
	now = f[now][b];
	now = f[now][c];
	now = f[now][d];
	return now;
}

void check(int a, int b, int c, int d) {
	int tmp, p = num[Num(a, b, c, d)];
	bool flag = 0;
	for(int i = 0; i <= 9; ++i)
		if(i != a) {
			tmp = num[Num(i, b, c, d)];
			if(f[tmp][p] == 0) flag = 1;
		}
	for(int i = 0; i <= 9; ++i)
		if(i != b) {
			tmp = num[Num(a, i, c, d)];
			if(f[tmp][p] == 0) flag = 1;
		}
	for(int i = 0; i <= 9; ++i)
		if(i != c) {
			tmp = num[Num(a, b, i, d)];
			if(f[tmp][p] == 0) flag = 1;
		}
	for(int i = 0; i <= 9; ++i)
		if(i != d) {
			tmp = num[Num(a, b, c, i)];
			if(f[tmp][p] == 0) flag = 1;
		}
	for(int i = 0; i <= 9; ++i)
		if(i != p && f[p][i] == 0) flag = 1;
	if(a != b) {
		tmp = num[Num(b, a, c, d)];
		if(f[tmp][p] == 0) flag = 1;
	}
	if(b != c) {
		tmp = num[Num(a, c, b, d)];
		if(f[tmp][p] == 0) flag = 1;
	}
	if(c != d) {
		tmp = num[Num(a, b, d, c)];
		if(f[tmp][p] == 0) flag = 1;
	}
	if(d != p) {
		tmp = num[Num(a, b, c, p)];
		if(f[tmp][d] == 0) flag = 1;
	}
	if(flag) ans++;
}
							 
int main() {
	Hzy("B");
	for(int i = 0; i <= 9; ++i)
		for(int j = 0; j <= 9; ++j) f[i][j] = read();
	for(int a = 0; a <= 9; ++a)
		for(int b = 0; b <= 9; ++b)
			for(int c = 0; c <= 9; ++c)
				for(int d = 0; d <= 9; ++d)
					num[Num(a, b, c, d)] = calc(a, b, c, d);
	for(int a = 0; a <= 9; ++a)
		for(int b = 0; b <= 9; ++b)
			for(int c = 0; c <= 9; ++c)
				for(int d = 0; d <= 9; ++d)
					check(a, b, c, d);
	printf("%d\n", ans);
	return 0;
}
