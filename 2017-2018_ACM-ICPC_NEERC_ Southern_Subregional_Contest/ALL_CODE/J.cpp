#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
struct Node {
	LL b, p;
	bool operator < (const Node & x) const {
		if(p != x.p) return p < x.p;
		else return b < x.b;
	}
}t[N];
LL t1[N * 2], t2[N * 2], s[N * 2], a[N], sz, n, m;
int fa[N];
int ans(0);
int find_fa(int x) {
	if(x != fa[x]) fa[x] = find_fa(fa[x]);
	return fa[x];
}
void mod1(int x, LL y) {
	for(; x > 0; x -= (x & (-x))) t1[x] = max(t1[x], y);
}
LL que1(int x) {
	LL res(0);
	for(; x <= sz; x += (x & (-x))) res = max(res, t1[x]);
	return res;
}
void mod2(int x, LL y) {
	for(; x <= n; x += (x & (-x))) t2[x] += y;
}
LL que2(int x) {
	LL res(0);
	for(; x > 0; x -= (x & (-x))) res += t2[x];
	return res;
}
map <LL, int> M;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("J");
	n = read(), m = read();
	LL pos, sum, tmp, pre;
	for(int i = 1; i <= n; ++i) {
		a[i] = read(), s[i] = a[i], fa[i] = i;
	}
	for(int i = 1; i <= m; ++i) {
		t[i].b = read();
		s[n + i] = t[i].b;
	}
	for(int i = 1; i <= m; ++i) t[i].p = read();
	sort(s + 1, s + n + m + 1);
	for(int i = 1;  i <= n + m; ++i) if(!M[s[i]]) M[s[i]] = ++sz;
	for(int i = 1; i <= n; ++i) mod1(M[a[i]], i), mod2(i, a[i]);
	sort(t + 1, t + m + 1);
	for(int i = 1; i <= m; ++i) {
		pos = que1(M[t[i].b]);
		sum = que2(pos);
		if(sum >= t[i].p) {
			ans++; tmp = t[i].p;
			for(; ;) {
				if(a[pos] >= tmp) {
					a[pos] -= tmp;
					mod2(pos, -tmp);
					tmp = 0;
				}
				else {
					tmp -= a[pos];
					mod2(pos, -a[pos]);
					a[pos] = 0;
				}
				if(a[pos] == 0) {
					pre = find_fa(pos - 1);
					fa[pos] = pre;
					pos = pre;
				}
				if(!tmp) break;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
