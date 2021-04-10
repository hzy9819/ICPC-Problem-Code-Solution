#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#include <map>
#define LL long long
#define db double
#define l first
#define r second
#define lson(o) (o << 1)
#define rson(o) ((o << 1) + 1)
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
	int l, r;
	int Min, ct, fg;
}a[N * 4];

void Update(int t) {
	a[t].Min = a[lson(t)].Min, a[t].ct = a[lson(t)].ct;
	if(a[lson(t)].Min == a[rson(t)].Min)
		a[t].ct += a[rson(t)].ct;
	else if(a[lson(t)].Min > a[rson(t)].Min)
		a[t].Min = a[rson(t)].Min, a[t].ct = a[rson(t)].ct;
}

void Pushdown(int t) {
	if(a[t].fg) {
		a[lson(t)].fg += a[t].fg; a[lson(t)].Min += a[t].fg;
		a[rson(t)].fg += a[t].fg; a[rson(t)].Min += a[t].fg;
		a[t].fg = 0;
	}
}

void Build(int l, int r, int t) {
	a[t].l = l, a[t].r = r;
	a[t].fg = 0;
	if(l == r) {
		a[t].ct = a[t].Min = 1;
		return ;
	}

	int mid = (l + r) >> 1;
	Build(l, mid, lson(t));
	Build(mid + 1, r, rson(t));

	Update(t);
}

int A[N], n;

stack <int> s1, s2;
map <int, int> M;
LL ans;

void add(int t, int l, int r, int ad) {
	if(l <= a[t].l && a[t].r <= r) {
		a[t].fg += ad;
		a[t].Min += ad;
		return ;
	}
	Pushdown(t);
	int mid = (a[t].l + a[t].r) >> 1;
	if(l <= mid)
		add(lson(t), l, r, ad);
	if(r > mid)
		add(rson(t), l, r, ad);
	Update(t);
}

int main() {
	int T = read(), cas = 0;
	while(T--) {
		cas++, ans = 0;
		n = read();
		for(int i = 1; i <= n; ++i)
			A[i] = read();
		Build(1, n, 1);
		while(!s1.empty())
			s1.pop();
		while(!s2.empty())
			s2.pop();
		M.clear();
		int pre = 0;
		for(int i = 1; i <= n; ++i) {
			while(!s1.empty()) {
				int tmp = s1.top();
				if(A[tmp] >= A[i])
					break;
				s1.pop();
				pre = s1.empty() ? 1 : s1.top() + 1;
				add(1, pre, tmp, -A[tmp]);
			}
			pre = s1.empty() ? 1 : s1.top() + 1;
			add(1, pre, i, A[i]);
			s1.push(i);

			while(!s2.empty()) {
				int tmp = s2.top();
				if(A[tmp] <= A[i])
					break;
				s2.pop();
				pre = s2.empty() ? 1 : s2.top() + 1;
				add(1, pre, tmp, A[tmp]);
			}
			pre = s2.empty() ? 1 : s2.top() + 1;
			add(1, pre, i, -A[i]);
			s2.push(i);

			pre = M.count(A[i]) ? M[A[i]] + 1 : 1;
			add(1, pre, i, -1);
			M[A[i]] = i;

			ans += a[1].ct;
		}
		printf("Case #%d: %lld\n", cas, ans);
	}
										
		
	return 0;
}
