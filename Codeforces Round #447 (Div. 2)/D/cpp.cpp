#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1000010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Node {
	int l, r;
	vector <int> v;
	vector <LL> s;
}a[N];
int n, m, q;
LL bin(int x, LL y) {
	if(y < 0) return 0;
	//if(!a[x].v.size()) return y;
	int l = 0, r = a[x].v.size() - 1;
	//if(y < a[x].v[0]) return y;
	if(y >= a[x].v[r]) return 1LL * (r + 1) * y - a[x].s[r];
	for(int mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
		if(y >= a[x].v[mid]) l = mid + 1;
		else r = mid - 1;
	}
	return 1LL * l * y - a[x].s[l - 1];
}
LL work(int x, LL y) {
	LL ans = bin(x, y), fa;
	fa = x / 2;
	if(fa * 2 == x) y -= a[fa].l;
	else y -= a[fa].r;
	while(y > 0 && fa) {
		ans += bin(fa, y);
		if(fa * 2 == x) ans -= bin(x, y - a[fa].l);
		else ans -= bin(x, y - a[fa].r);
		x = fa, fa = x / 2;
		if(fa * 2 == x) y -= a[fa].l;
		else y -= a[fa].r;
	}
	return ans;
}
int main() {
	Hzy("D");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		if(i * 2 <= n) a[i].l = read();
		if(i * 2 + 1 <= n) a[i].r = read();
	}
	for(int i = n; i >= 1; --i) {
		a[i].v.push_back(0);
		if(!a[i].l && !a[i].r) ;
		else if(!a[i].r) a[i].v.push_back(a[i].l);
		else if(!a[i].l) a[i].v.push_back(a[i].r);
		else {
			int lsz = a[i * 2].v.size(), rsz = a[i * 2 + 1].v.size(), p1 = 0, p2 = 0, t1, t2;
			while(p1 < lsz || p2 < rsz) {
				if(p1 == lsz) a[i].v.push_back(a[i * 2 + 1].v[p2++] + a[i].r);
				else if(p2 == rsz) a[i].v.push_back(a[i * 2].v[p1++] + a[i].l);
				else {
					t1 = a[i * 2].v[p1] + a[i].l, t2 = a[i * 2 + 1].v[p2] + a[i].r;
					if(t1 <= t2) a[i].v.push_back(t1), p1++;
					else a[i].v.push_back(t2), p2++;
				}
			}
		}
		for(int j = 0; j < a[i].v.size(); ++j) a[i].s.push_back(j ? a[i].s[j - 1] + a[i].v[j] : a[i].v[j]);
	}
	int x, y;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		printf("%I64d\n", work(x, (LL) y));
	}		
	return 0;
}
