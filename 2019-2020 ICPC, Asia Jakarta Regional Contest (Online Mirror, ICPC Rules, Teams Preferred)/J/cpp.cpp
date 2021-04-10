#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int weg = 1e9 + 7;
char s[N];
int f[N][55], blk = 0;
int n, m, G1, G2, G3, ans = 0;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	n = read(), m = read();
	G1 = read(), G2 = read(), G3 = read();
	scanf("%s", s + 1);
	memset(f, -1, sizeof f);
	f[0][0] =0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= 50; ++j) {
			f[i][j] = f[i - 1][j];
			if(i >= 2 && s[i] == s[i - 1] && s[i] == '.' && f[i - 2][j] != -1)
				f[i][j] = max(f[i][j], f[i - 2][j] + 1);
			if(i >= 3 && j > 0 && s[i] == s[i - 2] && s[i] == '.' && s[i - 1] == '#')
				f[i][j] = max(f[i][j], f[i - 3][j - 1]);
		}
	for(int i = 1; i <= n; ++i)
		blk += (s[i] == '#');
	for(int i = 0; i <= 50; ++i) {
		if(f[n][i] == -1)
			continue;
		int tmp = n - f[n][i] * 2 - i * 3 - (blk - i);
		if(m <= tmp)
			ans = max(ans, m * G1 + f[n][i] * G2 + i * G3);
		else {
			ans = max(ans, tmp * G1 + f[n][i] * G2 + i * G3);
			if(G1 + G1 <= G2)
				continue;
			int tp = m - tmp;
			if(tp / 2 >= f[n][i])
				ans = max(ans, (f[n][i] * 2 + tmp) * G1 + i * G3);
			else {
				if(tp % 2 && G1 > G2)
					ans = max(ans, ((tp / 2) * 2 + 1 + tmp) * G1 + i * G3 + (f[n][i] - tp / 2 - 1) * G2);
				else
					ans = max(ans, ((tp / 2) * 2 + tmp) * G1 + i * G3 + (f[n][i] - tp / 2) * G2);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
