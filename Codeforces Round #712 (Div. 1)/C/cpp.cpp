#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int INF = 1 << 30;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, s[N];
pair <int, int> a[N];

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i].l = read(), a[i].r = read();
	sort(a + 1, a + n + 1);
	int now = 0;
	LL res = 0;
	for(int i = 1; i <= n; ++i) {
		//	if(i != n && a[i + 1].l - a[i].l < a[i].r) {
		//	int pos = upper_bound(a + i, a + n + 1, mk(a[i].l + a[i].r, INF) ) - a;
		now = max(now, a[i].l + a[i].r);
			//}
		res += a[i].r;
		if(i != n && now < a[i + 1].l)
			res += a[i + 1].l - now;
	}
	cout << res << endl;
			
			
	return 0;
}
