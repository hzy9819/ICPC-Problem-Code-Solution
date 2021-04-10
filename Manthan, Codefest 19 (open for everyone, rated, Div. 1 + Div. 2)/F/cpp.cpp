#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 2000010;
const int M = 25;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int a[N], n, Bt = 0, ans;
pair <int, int> S[N << 1];

void add(int msk, int t) {
	if(!t)
		return ;
	if(S[msk].l == 0)
		S[msk].l = t;
	else if(S[msk].r == 0 && S[msk].l != t) {
		S[msk].r = t;
		if(S[msk].l > S[msk].r)
			swap(S[msk].l, S[msk].r);
	}
	else if(S[msk].l < t && S[msk].r != t) {
		S[msk].l = t;
		if(S[msk].l > S[msk].r)
			swap(S[msk].l, S[msk].r);
	}
}

void Merge(int m1, int m2) {
	add(m2, S[m1].l);
	add(m2, S[m1].r);
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		add(a[i], i);
		while((1 << Bt) <= a[i])
			Bt++;
	}
	for(int i = 0; i < Bt; ++i)
		for(int j = 0; j < (1 << Bt); ++j)
			if(j & (1 << i))
				Merge(j, j ^ (1 << i));
	int tmp, tp;
	for(int i = 1; i <= n - 2; ++i) {
		tmp = (1 << Bt) - 1 - a[i];
		tp = 0;
		for(int j = Bt - 1; j >= 0; --j)
			if(tmp & (1 << j))
				if(S[tp ^ (1 << j)].l > i && S[tp ^ (1 << j)].r)
					tp ^= (1 << j);
		ans = max(ans, a[i] ^ tp);
	}
	cout << ans << endl;
	return 0;
}
