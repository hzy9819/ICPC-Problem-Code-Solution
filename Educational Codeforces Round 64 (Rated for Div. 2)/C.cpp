#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while(c != '-' && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL n, a[N], z, ans = 0;
bool b[N];

int main() {
	n = read(), z = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	sort(a + 1, a + n + 1);
	int l = 0, r = n / 2;
	for(int mid = (l + r) >> 1, fg = 1; l <= r; mid = (l + r) >> 1, fg = 1) {
		for(int i = 1; i <= mid; ++i)
			if(a[n - mid + i] - a[i] < z) {
				r = mid - 1;
				fg = 0;
				break;
			}
		if(fg)
			l = mid + 1, ans = mid;
	}
		
	cout << ans << endl;
	return 0;
}
