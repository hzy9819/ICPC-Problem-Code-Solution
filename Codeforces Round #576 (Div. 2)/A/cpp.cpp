#include <bits/stdc++.h>
#define LL long long
#define db double
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

int n, x, y, a[N];
int ans;
//LL pre[N], tail[N], cnt1 = 0, cnt2 = 0, hd1 = 1, hd2 = 1;

int main() {
	Hzy("A");
	n = read(), x = read(), y = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	
	for(int i = 1; i <= n; ++i) {
		int l = max(1, i - x), r = min(n, i + y);
		bool fg = 1;
		for(int j = l; j <= r; ++j)
			if(a[j] < a[i]) {
				fg = 0;
				break;
			}
		if(fg) {
			ans = i;
			break;
		}
	}
	
	cout << ans << endl;
	return 0;
}
