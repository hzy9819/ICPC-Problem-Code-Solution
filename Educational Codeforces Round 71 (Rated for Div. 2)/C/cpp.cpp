#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL f[N][2], a, b, ans, n;
char s[N];

int main() {
	int T = read();
	while(T--) {
		n = read(), a = read(), b = read();
		scanf("%s", s + 1);
		f[0][1] = 1e9;
		f[0][0] = b;
		for(int i = 1; i <= n; ++i) {
			f[i][1] = f[i - 1][1] + a + b * 2;
			if(f[i - 1][0] != -1 && s[i] == '0')
				f[i][1] = min(f[i][1], f[i - 1][0] + a * 2 + b * 2);
			if(s[i] == '0') {
				f[i][0] = f[i - 1][1] + a * 2 + b;
				if(f[i - 1][0] != -1)
					f[i][0] = min(f[i][0], f[i - 1][0] + a + b);
			}
			else
				f[i][0] = -1;
		}
		ans = f[n][0];
		cout << ans << endl;
	}
	return 0;
}
