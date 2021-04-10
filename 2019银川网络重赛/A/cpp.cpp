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

int a[N];
LL res;
int n, q;

int main() {
	freopen("A.in", "r", stdin);
	freopen("std.out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	int type, l, r, x;
	q = read();
	for(int i = 1; i <= q; ++i) {
		type = read();
		if(type == 1) {
			l = read(), r = read();
			res = 0;
			for(int j = l; j <= r; ++j)
				res += a[j];
			cout << res << endl;
		}
		else if(type == 2) {
			l = read(), r = read(), x = read();
			for(int j = l; j <= r; ++j)
				a[j] ^= x;
		}
		else if(type == 3) {
			l = read(), r = read(), x = read();
			for(int j = l; j <= r; ++j)
				a[j] |= x;
		}
		else if(type == 4) {
			l = read(), r = read(), x = read();
			for(int j = l; j <= r; ++j)
				a[j] &= x;
		}
	}
	return 0;
}
