#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const LL lim = 1e+18;
const int N = 20;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
vector <LL> a, b, A, B;
LL k, ans, n;
void Dfs(int t, LL now, vector <LL> & a, vector <LL> & A) {
	if(t == a.size()) return ;
	Dfs(t + 1, now, a, A);

	while(a[t] <= lim / now) {
		now *= a[t];
		A.push_back(now);
		Dfs(t + 1, now, a, A);
	}
}

bool check(LL t) {
	int p = B.size() - 1, tot = 0;
	bool fg = 0;
	for(int i = 0; i < A.size(); ++i) {
		if(A[i] > t) break;
		while(p >= 0 && (db) A[i] * B[p] > t ) p--;
		if(A[i] * B[p] == t) fg = 1;
		tot += p + 1;
		if(tot > k) break;
	}
	if(tot == k && fg) ans = t;
	return tot < k;
}
	
int main() {
	Hzy("E");
	n = read();
	for(int i = 1; i <= n; ++i) {
		if(i & 1) a.push_back(read());
		else b.push_back(read());
	}
	Dfs(0, 1, a, A);
	Dfs(0, 1, b, B);
	A.push_back(1), B.push_back(1);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	k = read();
	LL l = 1, r = lim;
	for(LL mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		if(check(mid)) l = mid + 1;
		else r = mid - 1;
	printf("%lld\n", ans);
	return 0;
}
