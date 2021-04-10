#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)

using namespace std;
const LL inf = (LL)2e18;
const int N = 2000010;

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c != '-') && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int h[N];
vector <int> ev[N];
LL ans[N], sum[N];

int main() {
	Hzy("landscape");
	int n;
	LL m;
	n = read(), m = read();
	for (int i = 0; i < n; i++) h[i] = read();
	int low = 0;
	for (int i = 0; i < n; i++) low = max(low, h[i]);
	int high = (int)1.01e9;
	while (low < high) {
		int mid = (low + high + 1) >> 1;
		for (int i = 0; i < n; i++) ans[i] = 0;
		for (int rt = 0; rt < 2; rt++) {
			sum[0] = h[0];
			for (int i = 1; i < n; i++) sum[i] = sum[i - 1] + h[i];
			for (int i = 0; i < n; i++) ev[i].clear();
			for (int i = 0; i < n; i++) {
				int j = i + mid - h[i];
				if (j < n) 
					ev[j].push_back(i);
				
			}
			int mx = -1;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < (int) ev[i].size(); j++) {
					mx = max(mx, ev[i][j]);
				}
				if (mx >= 0) {
					int from = mid - 1;
					int to = mid - (i - mx) + 1;
					ans[i] += (to + from) * 1LL * (from - to + 1) / 2;
					ans[i] -= (sum[i - 1] - sum[mx]);
				} else 
					ans[i] += inf;
			}
			for (int i = 0; i < n - i - 1; i++) {
				swap(h[i], h[n - i - 1]);
				swap(ans[i], ans[n - i - 1]);
			}
		}
		bool fg = false;
		for (int i = 0; i < n; i++) {
			ans[i] += mid - h[i];
			if (ans[i] <= m) {
				fg = true;
				break;
			}
		}
		if (fg) 
			low = mid;
		else 
			high = mid - 1;
	}
	printf("%d\n", low);
	return 0;
}
