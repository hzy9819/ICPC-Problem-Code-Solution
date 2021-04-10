#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
struct St {
	int a, b, x;
	bool operator < (const St & p) const {
		if(a != p.a) return a > p.a;
		else if(b != p.b) return b < p.b;
		else return x < p.x;
	}
}a[N];
int num[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m, now = 1;
priority_queue<St> Q;
int main() {
	Hzy("G");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i].x = i;
	int x, y; St tmp;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		a[x].a++, a[x].b += y;
		if(x == 1) {
			while(!Q.empty()) {
				tmp = Q.top();
				if(a[1] < tmp)  {
					num[tmp.x]--, Q.pop();
					if(num[tmp.x] == 0) now--;
				}
				else break;
			}
		}
		else {
			if(a[x] < a[1]) {
				if(!num[x]) now++;
				num[x]++;
				Q.push(a[x]);
			}
		}
		printf("%d\n", now);
	}
	return 0;
}
