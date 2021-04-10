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

LL n, m1, m2, cmp_d, rt;
struct Node {
    LL l, r;
    LL d[4], Max[4], Min[4];
}a[N];
bool cmp(Node x, Node y) { return x.d[cmp_d] < y.d[cmp_d]; }
inline void Updata(LL p, LL k) {
    for(int i = 0; i < 4; ++i) {
        a[p].Min[i] = min(a[p].Min[i], a[k].Min[i]);
        a[p].Max[i] = max(a[p].Max[i], a[k].Max[i]);
    }
}
inline LL Build(LL l, LL r, LL d) {
    cmp_d = d;
    LL mid = (l + r) >> 1;
    nth_element(a + 1 + l, a + 1 + mid, a + 1 + r, cmp);
    for(int i = 0; i < 4; ++i) a[mid].Min[i] = a[mid].Max[i] = a[mid].d[i];
    if(l != mid) a[mid].l = Build(l, mid - 1, (d + 1) % 4); else a[mid].l = 0;
    if(r != mid) a[mid].r = Build(mid + 1, r, (d + 1) % 4); else a[mid].r = 0;
    if(a[mid].r) Updata(mid, a[mid].r);
    if(a[mid].l) Updata(mid, a[mid].l);
    return mid;
}
LL x, y, z;
LL jl, ans, res;
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
	if(ans != -1) return ;
    LL d0 = 0, dl, dr;
	if(a[p].Min[2] > z) return ;
    if(a[p].d[2] > z) d0 += inf;
    if(d0 == 0) {
        d0 += Calc(a[p].d[0] - x) + Calc(a[p].d[1] - y);
        if(d0 < a[p].d[3]) {
            ans = p;
			res = a[p].d[2];
			a[p].d[2] = a[p].Max[2] = a[p].Min[2] = n + 1;
			a[p].d[3] = a[p].Max[3] = -1;
			if(a[p].r) Updata(p, a[p].r);
			if(a[p].l) Updata(p, a[p].l);
			return ;
        }
    }
    if(a[p].l) dl = getdis(a[p].l); else dl = inf + 1;
    if(a[p].r) dr = getdis(a[p].r); else dr = inf + 1;
    if(dl < dr) {
        if(dl < a[p].Max[3]) ask(a[p].l);
		if(ans != -1) {
			Updata(p, a[p].l);
			return ;
		}
        if(dr < a[p].Max[3]) ask(a[p].r);
		if(ans != -1) {
			Updata(p, a[p].r);
			return ;
		}
    }
    else {
        if(dr < a[p].Max[3]) ask(a[p].r);
		if(ans != -1) {
			Updata(p, a[p].l);
			return ;
		}
        if(dl < a[p].Max[3]) ask(a[p].l);
		if(ans != -1) {
			Updata(p, a[p].r);
			return ;
		}
    }
}
                
inline LL read() {
    LL w(0), f(0); char c = getchar();
    while((c < '0' || c > '9') && c != '-') c = getchar();
    if(c == '-') f = 1, c = getchar();
    while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
    return f ? -w : w;
}
struct Que {
	int x, y, t;
}Q[N];

int main() {
	Hzy("A");
    int typ;
	n = read();
	for(int i = 1; i <= n; ++i) {
		typ = read();
		if(typ == 1) {
			a[++m1].d[0] = read();
			a[m1].d[1] = read();
			a[m1].d[2] = i;
			a[m1].d[3] = a[m1].d[1] * a[m1].d[1];
			
			a[m1].l = a[m1].r = 0;
		}
		else {
			Q[++m2].x = read();
			Q[m2].y = read();
			Q[m2].t = i;
		}
	}
	rt = Build(1, m1, 0);
	for(int i = 1; i <= m2; ++i) {
		x = Q[i].x, y = Q[i].y, z = Q[i].t;
		ans = -1;
		ask(rt);
		if(ans != -1) {
			cout << res << endl;
			//a[ans].d[2] = n + 1;
		}
		else puts("-1");
	}
	//}
    return 0;
}
