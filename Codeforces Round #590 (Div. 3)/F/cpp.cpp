#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
const int LIM = (1 << 20) + 10;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, ans, f[LIM];
char s[N];
int main() {
	scanf("%s", s);
	n = strlen(s);
	for(int i = 0; i < n; i++)
		for(int j = i, m = 0; j < n; j++) {
		if (m & 1 << (s[j] - 'a')) break;
		f[m] = max(f[m |= 1 << (s[j] -'a')], j  - i + 1);
	}
	for(int m = 0; m < (1 << 20); m++)
		for(int j = 0; j < 20; j++)
			if (m & (1 << j))
				f[m] = max(f[m], f[m ^ (1 << j)]);
	for(int m = 0; m < (1 << 20); m++)
		ans = max(ans, f[m] + f[~m & (1 << 20) - 1]);
	printf("%d", ans);
	return 0;
}
