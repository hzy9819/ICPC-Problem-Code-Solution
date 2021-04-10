#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 2010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int x_min[N], x_max[N], y_max[N], y_min[N], res[N], ans, base = 0;
int n, k;
char s[N];

int main() {
	n = read(), k = read();
	memset(x_min, -1, sizeof x_min);
	memset(x_max, -1, sizeof x_max);
	memset(y_max, -1, sizeof y_max);
	memset(y_min, -1, sizeof y_min);
	for(int i = 0; i < n; ++i) {
		scanf("%s", s);
		for(int j = 0; j < n; ++j)
			if(s[j] == 'B') {
				x_max[i] = max(x_max[i], j);
				x_min[i] = x_min[i] == -1 ? j : min(x_min[i], j);
				y_max[j] = max(y_max[j], i);
				y_min[j] = y_min[j] == -1 ? i : min(y_min[j], i);
			}
	}
	for(int i = 0; i < n; ++i) {
		if(x_min[i] < 0)
			base++;
		if(y_min[i] < 0)
			base++;
	}
	for(int i = 0; i + k - 1 < n; ++i) {
		memset(res, 0, sizeof res);
		for(int j = 0; j < k; ++j) {
			if(x_max[i + j] >= 0 && x_max[i + j] - x_min[i + j] < k)
				res[max(0, x_max[i + j] - k + 1)]++, res[x_min[i + j] + 1]--;
		}
		int now = res[0];
		for(int j = 0; j < k; ++j) 
			if(y_min[j] >= i && y_max[j] <= i + k - 1)
				now++;
		ans = max(ans, now);
		for(int j = 1; j + k - 1 < n; ++j) {
			now += res[j];
			if(y_min[j - 1] >= i && y_max[j - 1] <= i + k - 1)
				now--;
			if(y_min[j + k - 1] >= i && y_max[j + k - 1] <= i + k - 1)
				now++;
			ans = max(ans, now);
		}
	}
	ans += base;
	cout << ans << endl;							   
	return 0;
}
