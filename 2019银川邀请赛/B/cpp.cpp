#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

const int N = 55;

struct Point {
	int x, y;
	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	db norm() const {
		return hypot((db) x, (db) y);
	}
}p[N];

Point operator - (Point a, Point b) {
	return Point(a.x - b.x, a.y - b.y);
}
int n;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	int T = read(), tc = 0;
	while(T--) {
		++tc;
		n = read();
		for(int i = 0; i < n; ++i)
			p[i].x = read(), p[i].y = read();
		p[n] = p[0], p[n + 1] = p[1];
		Point Q, t1, t2;
		Q.x = read(), Q.y = read();
		db ans = 0;
		for(int i = 0; i < n; ++i) {
			db r = (Q - p[i + 1]).norm();
			t1 = p[i + 1] - p[i];
			t2 = p[i + 2] - p[i + 1];
			ans += acos((db) (t1.x * t2.x + t1.y * t2.y) / (t1.norm() * t2.norm())) * r;
		}
		printf("Case #%d: %.3lf\n", tc, ans);
	}
	
	return 0;
}
