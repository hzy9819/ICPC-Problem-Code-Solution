#include <bits/stdc++.h>
#define LL long long
#define db double
#define mp make_pair
#define fir first
#define sec second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
priority_queue< pair <LL, pair<int, int> > >Q;
map< pair<int, int>, bool> M;
int n, m, r, k;
void Push(int x, int y) {
	if(x <= 0 || x > n || y <= 0 || y > m || M[mp(x, y)]) return ;
	M[mp(x, y)] = 1;
	LL ans = (LL) (min(x + r, n + 1) - max(r, x)) * (min(y + r, m + 1) - max(r, y));
	Q.push(mp(ans, mp(x, y)));
}
LL ans;

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("D");
	n = read(), m = read(), r = read(), k = read();
	for(int i = 1; i <= n; ++i) Push(i, m / 2 + 1);
	for(int i = 1; i <= k; ++i) {
		ans += Q.top().fir;
		int x = Q.top().sec.fir, y = Q.top().sec.sec;
		Q.pop();
		Push(x, y + 1);
		Push(x, y - 1);
		Push(x + 1, y);
		Push(x - 1, y);
	}
	printf("%.10lf\n", (db) ans / (n - r + 1) / (m - r + 1));
	return 0;
}
