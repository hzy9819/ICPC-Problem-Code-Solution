#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
LL a[N], s[N];
struct Num {
	LL a, b;
}ans;
const LL weg = (1e+17);
void add(LL t) {
	ans.a += (ans.b + t) / weg;
	ans.b = (ans.b + t) % weg;
}
	
int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + a[i];
	int t = n;
	for(int i = n; i >= 1; --i) {
		while(t && a[t - 1] >= a[i] - 1) t--;
		add(t * a[i] - s[t]);
	}
	if(ans.a) printf("%lld%016lld\n", ans.a, ans.b);
	else printf("%lld\n", ans.b);
	return 0;
}
