#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while(c != '-' && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL n, x, ans;

pair <int, int> a[N];
set <int> S;

int main() {
	Hzy("E");
	n = read(), x = read();
	for(int i = 1; i <= n; ++i)
		a[i].r = read();
	int Min = x + 1, lim = 1, Lim = x;
	for(int i = n; i >= 1; --i) {
		a[i].l = Min;
		if(a[i].r > Min) Lim = min(Lim, a[i].r);
		Min = min(a[i].r, Min);
		
		set <int>::iterator it = S.lower_bound(-a[i].r + 1);
		if(it != S.end())
			lim = max(lim, -(*it));
		S.insert(-a[i].r);
	}
	sort(a + 1, a + n + 1);
	int p = 1;
	for(int i = 1; i <= Lim; ++i) {
		while(i > a[p].l && p <= n) 
			lim = max(lim, a[p++].r);
		lim = max(lim, i);
		ans += x - lim + 1;
	}
	cout << ans << endl;
	return 0;
}
