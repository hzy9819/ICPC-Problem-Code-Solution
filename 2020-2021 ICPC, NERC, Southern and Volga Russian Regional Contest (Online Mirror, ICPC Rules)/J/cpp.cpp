#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

struct Edge {
	int x, y, w;
	bool operator < (const Edge & _) {
		return w < _.w;
	}
}e[N];

int n, m, k, fa[N];

int find_fa(int x) {
	if(fa[x] != x)
		fa[x] = find_fa(fa[x]);
	return fa[x];
}

LL ans;

int main() {
	int T = read();
	while(T--) {
		n = read(), m = read(), k = read();
		ans = 1LL << 60;
		for(int i = 1; i <= n; ++i)
			fa[i] = i;
		int x, y;
		for(int i = 1; i <= m; ++i) 
			e[i].x = read(), e[i].y = read(), e[i].w = read();
		sort(e + 1, e + m + 1);
		int cnt = 0, tmp;
		LL cc = 0;
		for(int i = 1; i <= m; ++i) {
			x = find_fa(e[i].x), y = find_fa(e[i].y);
			if(x == y)
				continue;
			if(e[i].w > k)
				cc += e[i].w - k;
			fa[x] = y, cnt ++;
			if(cnt == n - 1) {
				tmp = i;
				break;
			}
		}
		if(e[tmp].w <= k) 
			for(int i = tmp; i <= m; ++i)
				ans = min(ans, (LL) abs(e[i].w - k));
		else
			ans = cc;
		cout << ans << endl;
	}
		
	return 0;
}
