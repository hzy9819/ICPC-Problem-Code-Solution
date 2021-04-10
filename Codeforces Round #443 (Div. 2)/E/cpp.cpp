#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 50010;
const int K = 15;
int n, k, a[N][K];
int v[K];
struct Node {
	int Minv[K], Maxv[K], sz;
	bool operator < (const Node & x) const {
		for(int i = 1; i <= k; ++i) 
			if(Maxv[i] > x.Maxv[i]) return 0;
		return 1;
	}
};
set <Node> s;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("E");
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) {
		Node now;
		for(int j = 1; j <= k; ++j) {
			a[i][j] = read(), v[j] = a[i][j];
			now.Minv[j] = a[i][j];
			now.Maxv[j] = a[i][j];
		}
		now.sz = 1;
		set <Node>::iterator x = s.lower_bound(now), y;
		while(x != s.end()) {
			bool fg = 0;
			for(int j = 1; j <= k; ++j)
				if(v[j] > x->Minv[j]) {
					fg = 1;
					break;
				}
			if(fg) {
				for(int j = 1; j <= k; ++j) {
					now.Minv[j] = min(now.Minv[j], x->Minv[j]);
					now.Maxv[j] = max(now.Maxv[j], x->Maxv[j]);
				}
				now.sz += x->sz;
				y = x; y++;
				s.erase(x);
				x = y;
			}
			else break;
		}
		s.insert(now);
		printf("%d\n", s.rbegin()->sz);
	}
	return 0;
}
