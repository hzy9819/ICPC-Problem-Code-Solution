#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

const int N = 200010;

struct Node {
	int l, r, num;
	int x;
}a[N << 2];

int n;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void Build(int t, int l, int r) {
	a[t].l = l, a[t].r = r, a[t].x = -1;
	if(l == r) {
		a[t].num = read();
		return ;
	}
	int mid = (l + r) >> 1;
	Build(t << 1, l, mid);
	Build((t << 1) + 1, mid + 1, r);
}

void Pushdown(int t) {
	if(a[t].x != -1) {
		a[t << 1].x = max(a[t << 1].x, a[t].x), a[t << 1].num = max(a[t].x, a[t << 1].num);
		a[(t << 1) + 1].x = max(a[(t << 1) + 1].x, a[t].x), a[(t << 1) + 1].num = max(a[t].x, a[(t << 1) + 1].num);
		a[t].x = -1;
	}
}

int Query(int t, int x) {
	if(a[t].l == a[t].r)
		return a[t].num;
	int mid = (a[t].l + a[t].r) >> 1;
	Pushdown(t);
	if(x <= mid)
		return Query(t << 1, x);
	else
		return Query((t << 1) + 1, x);
}

void Modify(int t, int p, int x) {
	if(a[t].l == a[t].r) {
		a[t].num = x;
		return ;
	}
	int mid = (a[t].l + a[t].r) >> 1;
	Pushdown(t);
	if(p <= mid)
		Modify(t << 1, p, x);
	else
		Modify((t << 1) + 1, p, x);
}
	
int main() {
	Hzy("D");
	n = read();
	Build(1, 1, n);
	int q = read();
	int tp, p, x;
	for(int i = 1; i <= q; ++i) {
		tp = read();
		if(tp == 1) {
			p = read(), x = read();
			Modify(1, p, x);
		}
		else {
			x = read();
			a[1].x = max(a[1].x, x), a[1].num = max(a[1].num, a[1].x);
		}
	}
	for(int i = 1; i <= n; ++i)
		printf("%d ", Query(1, i));
	return 0;
}
