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
LL t[N], tim[N];
void Modify(int x, int d) {
	for(; x <= n; x += (x & (-x))) t[x] += d;
}
int Que(int x) {
	int res(0);
	for(; x > 0; x -= (x & (-x))) res += t[x];
	return res;
}
int Sum(int l, int r) {
	if(r < l) return 0;
	if(l < 1) l = 1;
	if(r > n) r = n;
	return Que(r) - Que(l - 1);
}

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

queue <Event> W;
void Assign(Event tmp, LL now) {
	LL l, r, mid, x, p, a, b;
	for(l = 0, r = n, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		if(Sum(tmp.a - mid, tmp.a + mid)) r = mid - 1, x = mid;
		else l = mid + 1;
	//x = r + 1;
	if(tmp.a - x < 1 || v[tmp.a - x].empty()) {
		p = v[tmp.a + x].front();
		v[tmp.a + x].pop();
		Modify(tmp.a + x, -1);
	}
	else if(tmp.a + x > n || v[tmp.a + x].empty()) {
		p = v[tmp.a - x].front();
		v[tmp.a - x].pop();
		Modify(tmp.a - x, -1);
			}
	else {
		a = v[tmp.a - x].front();
		b = v[tmp.a + x].front();
		if(tim[a] < tim[b]) p = a;
		else if(tim[b] < tim[a]) p = b;
		else if(a < b) p = a;
		else p = b;
		if(p == a) {v[tmp.a - x].pop(); Modify(tmp.a - x, -1);}
		else {v[tmp.a + x].pop(); Modify(tmp.a + x, -1);}
	}
	printf("%I64d %I64d\n", p, x + now - tmp.t);
	tmp.tp = 1, tmp.t = now + x + abs(tmp.b - tmp.a), tmp.a = p;
	Q.push(tmp);
}
int main() {
	Hzy("L");
	n = read(), k = read(), m = read();
	LL x;
	for(int i = 1; i <= k; ++i) {
		x = read();
		v[x].push(i);
		Modify(x, 1);
	}
	LL t, a, b, now; Event tmp, tp;
	for(int i = 1; i <= m; ++i) {
		t = read(), a = read(), b = read();
		tmp.tp = 0, tmp.t = t, tmp.a = a, tmp.b = b;
		Q.push(tmp);
	}
	//int l, r, mid;
	while(!Q.empty()) {
		tmp = Q.top(), Q.pop();
		//pre = now;
		now = tmp.t;
		if(tmp.tp == 0) {
			if(Que(n) == 0) {W.push(tmp); continue;}
			Assign(tmp, now);		
		}
		else {
			v[tmp.b].push(tmp.a); Modify(tmp.b, 1); tim[tmp.a] = now;
			while(!Q.empty()) {
				tp = Q.top();
				if(tp.tp == 0 || tp.t != now) break;
				v[tp.b].push(tp.a); Modify(tp.b, 1); tim[tp.a] = now;
				Q.pop();
			}
			while(!W.empty() && Que(n)) {
				tp = W.front(), W.pop();
				Assign(tp, now);
			}						
		}
	}
	return 0;
}
