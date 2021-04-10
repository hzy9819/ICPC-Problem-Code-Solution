#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

struct Node {
	int l, r, Min;
	int add;
}a[N << 3];

int n, m, q, rk[N];

vector <int> v[N];

void Pushdown(int t) {
	if(!a[t].add)
		return ;
	int l = t << 1, r = l + 1;
	a[t].Min += a[t].add;
	a[l].add += a[t].add, a[r].add += a[t].add;
	a[t].add = 0;
}

void Update(int t) {
	if(a[t].l == a[t].r)
		return ;
	int l = t << 1, r = l + 1;
	Pushdown(l), Pushdown(r);
	a[t].Min = min(a[l].Min, a[r].Min);
}

int Que(int t, int l, int r) {
	Pushdown(t);
	if(a[t].l >= l && a[t].r <= r)
		return a[t].Min;
	int mid = (a[t].l + a[t].r) >> 1;
	if(mid >= r)
		return Que(t << 1, l, r);
	else if(mid > l)
		return Que((t << 1) + 1, l, r);
	else
		return min(Que(t << 1, l, mid), Que((t << 1) + 1, mid + 1, r));
}

void Add(int t, int l, int r, int ad) {
	Pushdown(t);
	if(a[t].l >= l && a[t].r <= r) {
		a[t].add += ad;
		return ;
	}
	int mid = (a[t].l + a[t].r) >> 1;
	if(mid >= r)
		Add(t << 1, l, r, ad);
	else if(mid < l)
		Add((t << 1) + 1, l, r, ad);
	else {
		Add(t << 1, l, mid, ad);
		Add((t << 1) + 1, mid + 1, r, ad);
	}
	Update(t);
}

void Build(int t, int l, int r) {
	a[t].l = l, a[t].r = r;
	if(l >= r) {
		a[t].Min = rk[l];
		a[t].add = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	Build(t << 1, l, mid);
	Build((t << 1) + 1, mid + 1, r);
	Update(t);
}


int main() {
	n = read(), m = read(), q = read();
	int now = 0, a1 = read(), x, y, z, len;
	for(int i = 2; i <= n; ++i) {
		x = read();
		if(x < a1)
			now++;
	}
	for(int i = 1; i <= m; ++i) {
		len = read();
		now -= len;
		rk[i] = now;
		for(int j = 1; j <= len; ++j) {
			x = read();
			v[i].push_back(x);
			if(x < a1)
				now++;
		}
	}
	Build(1, 1, m);
	for(int i = 1; i <= q; ++i) {
		x = read(), y = read(), z = read();
		if(x < m) {
			if(v[x][y - 1] < a1 && z > a1)
				Add(1, x + 1, m, -1);
			if(v[x][y - 1] > a1 && z < a1)
				Add(1, x + 1, m, 1);
		}
		v[x][y - 1] = z;
		x = Que(1, 1, m);
		if(x < 0)
			puts("0");
		else
			puts("1");
	}
	return 0;
}
