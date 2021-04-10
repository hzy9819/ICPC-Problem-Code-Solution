#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

const int N = 100;
const db eps = 1e-8;

struct Vector {
	db x, y;
};

inline Vector operator - (Vector a, Vector b) {
	Vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

inline double Sqr(db a) { return a * a; }

inline int Sign(db a) {
	if(fabs(a) <= eps)
		return 0;
	return a < 0 ? -1 : 1;
}

inline bool operator < (Vector a, Vector b) {
	return Sign(b.y - a.y) > 0 || Sign(b.y - a.y) == 0 && Sign(b.x - a.x) > 0;
}

inline db Max(db a, db b) { return a > b ? a : b; }
inline db Length(Vector a) { return sqrt(Sqr(a.x) + Sqr(a.y)); }
inline db Cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

Vector dot[N], List[N];
db opt[N][N];
int seq[N];
int n, len;
db ans;

bool Cmp(Vector a, Vector b) {
	int temp = Sign(Cross(a, b));
	if(temp != 0)
		return temp > 0;
	temp = Sign(Length(b) - Length(a));
	return temp > 0;
}

void Solve(int vv) {
	int t, i, j, _len;
	for(i = len = 0; i < n; ++i)
		if(dot[vv] < dot[i])
			List[len++] = dot[i] - dot[vv];
	for(i = 0; i < len; ++i)
		for(j = 0; j < len; ++j)
			opt[i][j] = 0;
	sort(List, List + len, Cmp);
	db v;
	for(t = 1; t < len; ++t) {
		_len = 0;
		for(i = t - 1; i >= 0 && Sign(Cross(List[t], List[i])) == 0; --i);
		while(i >= 0) {
			v = Cross(List[i], List[t]) / 2;
			seq[_len++] = i;
			for(j = i - 1; j >= 0 && Sign(Cross(List[i] - List[t], List[j] - List[t])) > 0; j--);
			if(j >= 0)
				v += opt[i][j];
			ans = Max(ans, v);
			opt[t][i] = v;
			i = j;
		}
		for(i = _len - 2; i >= 0; --i)
			opt[t][seq[i]] = Max(opt[t][seq[i]], opt[t][seq[i + 1]]);
	}
}

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	int T = read();
	while(T--) {
		n = read();
		ans = 0.0;
		for(int i = 0; i < n; ++i)
			dot[i].x = read(), dot[i].y = read();
		for(int i = 0; i < n; ++i)
			Solve(i);
		printf("%.1lf\n", ans);
	}
		
	return 0;
}
