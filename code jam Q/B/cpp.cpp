#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
const int INF = 1e6;
int n, T, X, Y, f[N][2];
string s;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	T = read();
	for(int cas = 1; cas <= T; ++cas) {
		X = read(), Y = read();
		cin >> s;
		n = s.size();
		f[0][0] = f[0][1] = 0;
		if(s[0] == 'C')
			f[0][1] = INF;
		if(s[0] == 'J')
			f[0][0] = INF;
		for(int i = 1; i < n; ++i) {
			f[i][0] = min(f[i - 1][0], f[i - 1][1] + Y);
			f[i][1] = min(f[i - 1][1], f[i - 1][0] + X);
			if(s[i] == 'C')
				f[i][1] = INF;
			if(s[i] == 'J')
				f[i][0] = INF;
		}
		printf("Case #%d: %d\n", cas, min(f[n - 1][0], f[n - 1][1]));
	}
	return 0;
}
