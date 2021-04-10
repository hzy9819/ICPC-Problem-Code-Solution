#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;
struct Point {
	Point() {}
	Point(LL _x, int _y) : x(_x), y(_y) {}
	LL x, y;
};

struct Seg {
	Point a, b;
}l[N];
LL ans;
map <pair <int, int>, bool> M, m[N];
int n;

LL gcd(LL a, LL b) {
	if(a < b) swap(a, b);
	int c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

bool Cross(Seg a, Seg b, Point & p) {
	LL x1 = a.a.x, x2 = a.b.x, y1 = a.a.y, y2 = a.b.y, ka = gcd(abs(x1 - x2), abs(y1 - y2));
	LL x3 = b.a.x, x4 = b.b.x, y3 = b.a.y, y4 = b.b.y, kb = gcd(abs(x3 - x4), abs(y3 - y4));
	LL xa = (x2 - x1) / ka, ya = (y2 - y1) / ka, xb = (x4 - x3) / kb, yb = (y4 - y3) / kb;
	LL X = x3 - x1, Y = y3 - y1;
	if(xa * yb == xb * ya) return 0;
	LL t1 = Y * xa - X * ya, t2 = xb * ya - yb * xa;
	if(t1 % t2) return 0;
	LL k = t1 / t2;
	//if(abs(k * xb) > abs(x4 - x3)) return 0;
	p.x = x3 + k * xb, p.y = y3 + k * yb;
	if(p.x < min(x3, x4) || p.x > max(x3, x4) || p.y < min(y3, y4) || p.y > max(y3, y4)) return 0;
	if(p.x < min(x1, x2) || p.x > max(x1, x2) || p.y < min(y1, y2) || p.y > max(y1, y2)) return 0;
	return 1;
}

int main() {
	Hzy("E");
	n = read();
	LL x1, y1, x2, y2;
	for(int i = 1; i <= n; ++i) {
		x1 = read(), y1 = read(), x2 = read(), y2 = read();
		l[i].a = Point(x1, y1), l[i].b = Point(x2, y2);
		ans += gcd(abs(x1 - x2), abs(y1 - y2)) + 1;
	}
	Point tmp;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(i != j && Cross(l[i], l[j], tmp)) {
				if(!m[i][make_pair(tmp.x, tmp.y)]) {
					m[i][make_pair(tmp.x, tmp.y)] = 1;
					ans--;
				}
				if(!M[make_pair(tmp.x, tmp.y)]) {
					M[make_pair(tmp.x, tmp.y)] = 1;
					ans++;
				}
			}
	cout << ans << endl;
				
	return 0;
}
