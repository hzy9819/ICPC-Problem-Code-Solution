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
const int N = 200010;
int n, k, m;
struct Event {
	int tp; //0 means taxi ride, 1 means taxi arrive
	LL t, a, b;
	bool operator < (const Event & p) const{
		if(t != p.t) return t > p.t;
		else if(tp != p.tp) return tp < p.tp;
		else if(a != p.a) return a > p.a;
		else return b > p.b;
	}
};
priority_queue <Event> Q;
queue <int> v[N];
int t[N], tim[N], tx[N];
void Modify(int *t, int x, int d) {
	for(; x <= n; x += (x & (-x))) t[x] += d;
}
int Que(int *t, int x) {
	int res(0);
	for(; x > 0; x -= (x & (-x))) res += t[x];
	return res;
}
int Sum(int *t, int l, int r) {
	if(r < l) return 0;
	if(l < 1) l = 1;
	if(r > n) r = n;
	return Que(t, r) - Que(t, l - 1);
}

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

queue <Event> W;

int main() {
	Hzy("L");
	n = read(), k = read(), m = read();
	LL x, p;
	for(int i = 1; i <= k; ++i) {
		x = read();
		v[x].push(i);
		Modify(t, x, 1);
	}
	LL ti, a, b, now, pre; Event tmp, tp;
	for(int i = 1; i <= m; ++i) {
		ti = read(), a = read(), b = read();
		tmp.tp = 0, tmp.t = ti, tmp.a = a, tmp.b = b;
		Q.push(tmp);
	}
	int l, r, mid;
	while(!Q.empty()) {
		tmp = Q.top(), Q.pop();
		pre = now, now = tmp.t;
		if(tmp.tp == 0) {
			if(Que(t, n) == 0) {W.push(tmp); continue;}
			for(l = 0, r = n, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
				if(Sum(t, tmp.a - mid, tmp.a + mid)) r = mid - 1;
				else l = mid + 1;
			x = r + 1;
			if(tmp.a - x < 1 || v[tmp.a - x].empty()) {
				p = v[tmp.a + x].front();
				v[tmp.a + x].pop();
				Modify(t, tmp.a + x, -1);
			}
			else if(tmp.a + x > n || v[tmp.a + x].empty()) {
				p = v[tmp.a - x].front();
				v[tmp.a - x].pop();
				Modify(t, tmp.a - x, -1);
			}
			else {
				a = v[tmp.a - x].front();
				b = v[tmp.a + x].front();
				if(tim[a] < tim[b]) p = a;
				else if(tim[b] < tim[a]) p = b;
				else if(a < b) p = a;
				else p = b;
				if(p == a) {v[tmp.a - x].pop(); Modify(t, tmp.a - x, -1);}
				else {v[tmp.a + x].pop(); Modify(t, tmp.a + x, -1);}
			}
			printf("%I64d %I64d\n", p, x);
			tmp.tp = 1, tmp.t = now + x + abs(tmp.b - tmp.a), tmp.a = p;
			Q.push(tmp);
		}
		else {
			if(!W.empty()) {
				tp = W.front(), W.pop();
				printf("%I64d %I64d\n", tmp.a, now - tp.t + abs(tmp.b - tp.a));
				tmp.tp = 1, tmp.t = now + abs(tmp.b - tp.a) + abs(tp.b - tp.a), tmp.b = tp.b;
				Q.push(tmp);
			}
			else {
				v[tmp.b].push(tmp.a);
				Modify(tmp.b, 1);
				tim[tmp.a] = now;
			}
		}
	}
	return 0;
}
