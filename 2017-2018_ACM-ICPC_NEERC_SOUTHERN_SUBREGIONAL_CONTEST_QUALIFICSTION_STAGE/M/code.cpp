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
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, d, ans;
int a[N];

int main() {
	//Hzy("M");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	d = a[2] - a[1];
	bool fg(0);
	if(n == 2) ans = a[2] + d;
	else { 
		for(int i = 3; i <= n; ++i) if(a[i] != a[i - 1] + d) {
				ans = a[n];
				fg = 1;
				break;
			}
		if(!fg) ans = a[n] + d;
	}
	printf("%d\n", ans);		
	return 0;
}
