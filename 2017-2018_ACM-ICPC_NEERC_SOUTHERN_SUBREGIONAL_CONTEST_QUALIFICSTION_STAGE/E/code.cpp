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
const int N = 100010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, ans, pos[N], sz, p[N], sze;
char c[N];
void impos() {
	puts("-1");
	exit(0);
}
int calc(int t, int l, int r) {
	if(t > r) return t - l;
	else if(t < l) return r - t;
	else return r - l + min(t - l, r - t);
}
bool Judge(int lim) {
	for(int i = 1, pre = 1, tp; i <= sz; ++i) {
		tp = pre;
		while(calc(pos[i], p[tp], p[pre]) <= lim && pre < sze) pre++;
		if(pre >= sze && calc(pos[i], p[tp], p[pre]) <= lim) return 1;
	}
	return 0;
}
	
int main() {
	//Hzy("E");
	scanf("%d\n", &n);
	for(int i = 1; i <= n; ++i) {
		c[i] = getchar();
		if(c[i] == '*') p[++sze] = i;
		if(c[i] == 'P') pos[++sz] = i;
	}
	int l, r, mid;
	for(l = 1, r = 2 * n, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
		if(Judge(mid)) r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", r + 1);
	return 0;
}
