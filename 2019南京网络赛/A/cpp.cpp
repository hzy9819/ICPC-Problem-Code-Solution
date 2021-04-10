#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, m, p;
int calc(int x, int y) {
	if(x < 1 || x > n || y < 1 || y > n)
		return 0;
	int mid = (n + 1) / 2;
	LL L = max(abs(x - mid), abs(y - mid));
	LL st = n * n  - (L * 2 + 1) * (L * 2 + 1) + 1, res;
	if(x == mid + L)
		res = st + (mid + L - y);
	else if(x == mid - L)
		res = st + (L * 2) * 2 + y - (mid - L);
	else if(y == mid - L)
		res = st + (L * 2) + (mid + L - x);
	else
		res = st + (L * 2) * 3 + x - (mid - L);

	int cnt = 0;
	while(res)
		cnt += res % 10, res /= 10;
	return cnt;
	
}
pair < pair<int, int>, int> sq[N], que[N * 4];
int cnt;

int t[N], ans[N];

void add(int x, int ad) {
	if(x < 1)
		return ;
	for(; x <= n; x += x & (-x))
		t[x] += ad;
}
int Que(int x) {
	int res = 0;
	if(x > n)
		x = n;
	for(; x > 0; x -= x & (-x))
		res += t[x];
	return res;
}
	
int main() {
	int T = read(), x, y ;
	while(T--) {
		n = read(), m = read(), p = read();
		cnt = 0;
		for(int i = 1; i <= m; ++i) {
			sq[i].l.l = read(), sq[i].l.r = read();
			sq[i].r = calc(sq[i].l.l, sq[i].l.r);
		}
		for(int i = 1; i <= p; ++i) {
			x = read(), y = read();
			que[++cnt].l.l = x - 1, que[cnt].l.r = y - 1, que[cnt].r = i;
			que[++cnt].l.l = read(), que[cnt].l.r = read(), que[cnt].r = i;
			que[++cnt].l.l = x - 1, que[cnt].l.r = que[cnt - 1].l.r, que[cnt].r = -i;
			++cnt, que[cnt].l.l = que[cnt - 2].l.l, que[cnt].l.r = y - 1, que[cnt].r = -i;
		}
		sort(sq + 1, sq + m + 1);
		sort(que + 1, que + cnt + 1);
		memset(t, 0, sizeof t);
		memset(ans, 0, sizeof ans);
		int q = 1;
		for(int i = 1; i <= cnt; ++i) {
			while(q <= m && sq[q].l.l <= que[i].l.l)
				add(sq[q].l.r, sq[q].r), q++;
			int tmp = que[i].r;
			ans[abs(tmp)] += tmp > 0 ? Que(que[i].l.r) : -Que(que[i].l.r);
		}
		for(int i = 1; i <= p; ++i) {
			printf("%d", ans[i]);
			if(i != p)
				puts("");
		}
		if(T)
			puts("");
	}
	return 0;
}
