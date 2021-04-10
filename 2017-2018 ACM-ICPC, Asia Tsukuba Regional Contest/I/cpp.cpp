#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
int t[N];
int sum(int x) {
	int res = 0 ;
	for(; x < N; x += x & -x)
		res += t[x];
	return res;
}
void add(int x, int d) {
	for(; x; x -= x & -x)
		t[x] += d;
}
int a[N], n, ans1, ans2 = 1;
vector <int> Q[N], ins[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("I");
	n = read();
	int x, y;
	for(int i = 1; i <= n; ++i) {
		x = read(), y = read();
		a[x]++, a[y]--;
		Q[y].push_back(x);
		ins[x].push_back(y);
	}
	int now = 0;
	for(int i = 0; i < N; ++i) {
		now += a[i];
		ans1 = max(ans1, now);
	}
	for(int i = 0; i < N; ++i) {
		for(int x : Q[i])
			ans2 = max(ans2, sum(x + 1));
		for(int x : ins[i])
			add(x, 1);
	}
	printf("%d %d\n", ans2, ans1);
	return 0;
}
