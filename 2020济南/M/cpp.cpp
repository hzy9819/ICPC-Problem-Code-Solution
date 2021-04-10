#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

ULL read() {
	ULL f = 0, w = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-')
		c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9')
		w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

ULL L, g[110][110][2], num[110], bin[110], ans;
int m, a[110], f[110], ct[70];

ULL G(int n, int k, int bt) {
	if(n < 0 || k < 0)
		return 0;
	return g[n][k][bt];
}

int calc(ULL t) {
	int res = 0;
	while(t) {
		if(t & 1)
			res++;
		t >>= 1;
	}
	return res;
}

int main() {
	int T = read();
	bin[0] = 1;
	for(int i = 1; i <= 63; ++i)
		bin[i] = (bin[i - 1] << 1);
	while(T--) {
		m = read(), L = read();
		// memset(a, 0, sizeof a);
		ans = 0;
		for(int i = 0; i < m; ++i)
			a[i] = read();
		int cnt = 0;
		ULL tmp = L;
		// memset(f, 0, sizeof f);
		while(tmp) {
			if(tmp & 1)
				f[cnt++] = 1;
			else
				f[cnt++] = 0;
			tmp >>= 1;
		}
		ct[cnt] = 0;
		for(int i = cnt - 1; i >= 0; --i)
			ct[i] = ct[i + 1] + f[i];

		memset(num, 0, sizeof num);
		num[0] = f[0];
		for(int i = 1; i < 64; ++i)
			num[i] = num[i - 1] + bin[i] * f[i];
		
		memset(g[cnt], 0, sizeof(g[cnt]));
		for(int i = 70; i >= cnt; --i)
			g[i][0][0] = 1;
		for(int i = 1; i <= cnt; ++i) {
			int n = cnt - i;
			for(int k = 0; k <= i; ++k) {
				if(f[n] == 1)
					g[n][k][0] = G(n + 1, k - 1, 0);
				else
					g[n][k][0] = G(n + 1, k, 0);
				g[n][k][1] = G(n + 1, k - 1, 1) + G(n + 1, k, 1);
				if(f[n] == 1)
					g[n][k][1] += G(n + 1, k, 0);
			}
		}
		for(int pt = 0; pt < 128; ++pt) {
			int tp1 = 0, tp2 = 0; // tp1: 11..11{ } 0:even 1:odd, tp2: {number of 1} 011.111{ } 0: even 1: odd
			int tp, now = pt;
			bool fg = 0;
			if((calc(pt) & 1) == a[0])
				tp = 0;
			else
				tp = 1;
			for(int i = 1; i < m; ++i) {
				now++;
				if(now == 128) {
					if(tp == a[i])
						tp1 = 0;
					else
						tp1 = 1;
					now = 0;
				}
			 
				else {
					if(((calc(now) + tp + tp1) & 1) != a[i]) {
						fg = 1;
						break;
					}
				}
			}
			if(fg)
				continue;
			if(L < 128 && pt <= L && tp == 0) {
				ans++;
				continue;
			}
			if(pt + m - 1 < 128) {
				if(tp == 0)
					for(int j = 0; j <= cnt; j += 2) {
						ans += g[7][j][1];
						if(pt <= num[6])
							ans += g[7][j][0];
					}
				else
					for(int j = 1; j <= cnt; j += 2) {
						ans += g[7][j][1];
						if(pt <= num[6])
							ans += g[7][j][0];
					}
				continue;
			}
						
						
			if(tp1 == 0) {
				for(int i = 1; 6 + i + 1 < cnt; i += 2) {
					ULL suff = (bin[i] - 1) << 7;
					suff += pt;
					if(suff > num[6 + i + 1])
						fg = 1;
					else
						fg = 0;

					if(tp == 1) 
						for(int j = 1; j <= cnt; j += 2) {
							ans += g[6 + i + 2][j][1];
							if(fg == 0)
								ans += g[6 + i + 2][j][0];
						}
					else
						for(int j = 0; j <= cnt; j += 2) {
							ans += g[6 + i + 2][j][1];
							if(fg == 0)
								ans += g[6 + i + 2][j][0];
						}
				}
			} else {
				for(int i = 0; 6 + i + 1 < cnt; i += 2) {
					ULL suff = (bin[i] - 1) << 7;
					suff += pt;
					if(suff > num[6 + i + 1])
						fg = 1;
					else
						fg = 0;

					if(tp == 0)
						for(int j = 1; j <= cnt; j += 2) {
							ans += g[6 + i + 2][j][1];
							if(fg == 0)
								ans += g[6 + i + 2][j][0];
						}
					else
						for(int j = 0; j <= cnt; j += 2) {
							ans += g[6 + i + 2][j][1];
							if(fg == 0)
								ans += g[6 + i + 2][j][0];
						}
				}
			}
		}
		cout << ans << endl;
	}
				
	return 0;
}

