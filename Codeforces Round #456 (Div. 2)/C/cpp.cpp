#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int n, m;
struct Monster {
	LL maxhp, shp, re, t;
	int id;
	bool operator < (const Moster & p) const {
		return t > p.t;
	}
}a[N];
struct Event {
	LL t, id, hp;
	bool operator < (const Event & p) const {
		return t < p.t;
	}
}s[N];
LL bt, inc, dps;
priority_queue <Monster> Q;
int Up[N];
void Inf() {
	puts("-1");
	exit(0);
}
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	n = read(), m = read();
	bt = read(), inc = read(), dps = read();
	for(int i = 1; i <= n; ++i) { 
		a[i].maxhp = read(), a[i].shp = read(), a[i].re = read();
		a[i].id = i;
		if(a[i].maxhp <= dps) Inf();
		a[i].t = (dps - a[i].shp) / a[i].re;
		if(a[i].shp + a[i].re * (a[i].t + 1) <= dps) a[i].t++;
		Q.push(a[i]);
	}
	for(int i = 1; i <= m; ++i)
		s[i].t = read(), s[i].id = read(), s[i].hp = read();
	int cnt = 1;
	sort(s + 1, s + m + 1);
	Monst tmp;
	while(!Q.empty()) {
		tmp = Q.front(), Q.pop();
		if(tmp.t < 0) continue;
		if(Up(a[i].id
		
	return 0;
}
