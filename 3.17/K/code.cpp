#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define Calc(o) ((o) * (o))
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 55;
const int N = 200010;

LL n, m, cmp_d, rt;
struct Node {
	LL l, r;
	LL d[3], Max[3], Min[3];
	LL c;
	LL id;
}a[N];
bool cmp(Node x, Node y) { return x.d[cmp_d] < y.d[cmp_d]; }
inline void Updata(LL p, LL k) {
	for(int i = 0; i < 3; ++i) {
		a[p].Min[i] = min(a[p].Min[i], a[k].Min[i]);
		a[p].Max[i] = max(a[p].Max[i], a[k].Max[i]);
	}
}
inline LL Build(LL l, LL r, LL d) {
	cmp_d = d;
	LL mid = (l + r) >> 1;
	nth_element(a + 1 + l, a + 1 + mid, a + 1 + r, cmp);
	for(int i = 0; i < 3; ++i) a[mid].Min[i] = a[mid].Max[i] = a[mid].d[i];
	if(l != mid) a[mid].l = Build(l, mid - 1, (d + 1) % 3); else a[mid].l = 0;
	if(r != mid) a[mid].r = Build(mid + 1, r, (d + 1) % 3); else a[mid].r = 0;
	if(a[mid].r) Updata(mid, a[mid].r);
	if(a[mid].l) Updata(mid, a[mid].l);
	return mid;
}
LL x, y, z;
LL jl, ans;
inline LL getdis(LL p) {
	LL res = 0;
	if(z < a[p].Min[2]) return inf + 1;
	if(x > a[p].Max[0]) res += Calc(x - a[p].Max[0]);
	if(x < a[p].Min[0]) res += Calc(a[p].Min[0] - x);
	if(y > a[p].Max[1]) res += Calc(y - a[p].Max[1]);
	if(y < a[p].Min[1]) res += Calc(a[p].Min[1] - y);
	return res ;
}

inline void ask(LL p) {
	LL d0 = 0, dl, dr;
	if(a[p].d[2] > z) d0 += inf;
	if(d0 == 0) {
		d0 += Calc(a[p].d[0] - x) + Calc(a[p].d[1] - y);
		if(d0 < jl) {
			ans = p;
			jl = d0;
		}
		else if(d0 == jl) {
			if(a[p].id < a[ans].id)
				ans = p;
		}
	}
	if(a[p].l) dl = getdis(a[p].l); else dl = inf + 1;
	if(a[p].r) dr = getdis(a[p].r); else dr = inf + 1;
	if(dl < dr) {
		if(dl <= jl) ask(a[p].l);
		if(dr <= jl) ask(a[p].r);
	}
	else {
		if(dr <= jl) ask(a[p].r);
		if(dl <= jl) ask(a[p].l);
	}
}
				
inline LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("K");
	LL t;
	//scanf("%lld", &t);
	t = read();
	while(t--) {
		//scanf("%lld %lld", &n, &m);
		n = read(), m = read();
		for(int i = 1; i <= n; ++i) {
			for(int k = 0; k < 3; ++k) a[i].d[k] = read();
			a[i].l = a[i].r = 0;
			a[i].id = i;
		}
		rt = Build(1, n, 0);
		for(int i = 1; i <= m; ++i) {
			//scanf("%lld %lld %lld", &x, &y, &z);
			x = read(), y = read(), z = read();
			jl = inf;
			ans = -1;
			ask(rt);
			printf("%lld %lld %lld\n", a[ans].d[0], a[ans].d[1], a[ans].d[2]);
		}
	}
	return 0;
}
