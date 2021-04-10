#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 5010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
db x[N], y[N], z[N], r;

struct point {
  double x, y;
} p[N], o;

inline double sqr(double x) { return x * x; }

inline double dis(point a, point b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline bool cmp(double a, double b) { return fabs(a - b) < 1e-8; }

point geto(point a, point b, point c) {
	double a1, a2, b1, b2, c1, c2;
	point ans;
	a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y),
		c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
	a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y),
		c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
	if (cmp(a1, 0)) {
		ans.y = c1 / b1;
		ans.x = (c2 - ans.y * b2) / a2;
	} else if (cmp(b1, 0)) {
		ans.x = c1 / a1;
		ans.y = (c2 - ans.x * a2) / b2;
	} else {
		ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
		ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
	}
	return ans;
}

db calc() {
	// scanf("%d", &n);
	// for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
	db r;
	for (int i = 1; i <= n; i++) swap(p[rand() % n + 1], p[rand() % n + 1]);
	o = p[1];
	for (int i = 1; i <= n; i++) {
		if (dis(o, p[i]) < r || cmp(dis(o, p[i]), r)) continue;
		o.x = (p[i].x + p[1].x) / 2;
		o.y = (p[i].y + p[1].y) / 2;
		r = dis(p[i], p[1]) / 2;
		for (int j = 2; j < i; j++) {
			if (dis(o, p[j]) < r || cmp(dis(o, p[j]), r)) continue;
			o.x = (p[i].x + p[j].x) / 2;
			o.y = (p[i].y + p[j].y) / 2;
			r = dis(p[i], p[j]) / 2;
			for (int k = 1; k < j; k++) {
				if (dis(o, p[k]) < r || cmp(dis(o, p[k]), r)) continue;
				o = geto(p[i], p[j], p[k]);
				r = dis(o, p[i]);
			}
		}
	}
	return r;
	//printf("%.10lf\n%.10lf %.10lf", r, o.x, o.y);
	//return 0;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		scanf("%lf %lf %lf", x + i, y + i, z + i);
	for(int i = 1; i <= n; ++i)
		p[i].x = x[i], p[i].y = y[i];
	r = calc();
	for(int i = 1; i <= n; ++i)
		p[i].x = x[i], p[i].y = z[i];
	db tmp = calc();
	r = min(r, tmp);
	for(int i = 1; i <= n; ++i)
		p[i].x = y[i], p[i].y = z[i];
	tmp = calc();
	r = min(r, tmp);
	printf("%.10lf\n", r * 2);
	return 0;
}
