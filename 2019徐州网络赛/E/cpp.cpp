#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 500010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, m;
int st[N], a[N], sz = 0, ans[N];

int main() {
	Hzy("E");
	n = read(), m = read();
	for(int i = 0; i < n; ++i)
		a[i] = read();
	for(int i = n - 1; i >= 0; --i) {
		if(!sz || a[st[sz]] < a[i] + m)
			ans[i] = -1;
		else {
			int l, r, mid;
			for(l = 1, r = sz, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
				if(a[st[mid]] >= a[i] + m)
					r = mid - 1;
				else
					l = mid + 1;
			ans[i] = st[r + 1] - i - 1;
			/*
			  r = max(1, r);
			while(r > 1 && a[st[r - 1]] >= a[i] + m)
				r--;
			ans[i] = st[r] - i - 1;
			*/
		}
		if(!sz || a[i] > a[st[sz]]) st[++sz] = i;
	}
	for(int i = 0; i < n; ++i)
		printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
	return 0;
}
