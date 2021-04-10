#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int weg = 998244353;
const int N = 1000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
LL f[N][2];

int main() {
	freopen("list.txt", "w", stdout);
	n = 100000;
	f[0][0] = f[0][1] = f[1][0] = f[2][1] = f[4][1] = 1;
	int h = 3, K;
	for(int i = 5; i <= n; ++i) {
		if(i + 1 >= (1 << h))
			h++;
		K = min(i - (1 << (h - 1)) + 1, (1 << (h - 2)));
		for(int l = (i - K) / 2; l <= (i + K - 1) / 2; ++l)
			f[i][l & 1] = (f[i][l & 1] + f[l][!(l & 1)] * f[i - l - 1][1] % weg) % weg;
	}
	for(int i = 0; i <= n; ++i)
		if(f[i][0] || f[i][1])
			printf("%d\n", i);
	return 0;
}
