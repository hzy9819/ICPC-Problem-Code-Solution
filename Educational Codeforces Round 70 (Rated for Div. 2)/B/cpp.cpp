#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 15;
const int S = 2000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int f[N][N], ct[N][N];
char s[S];

LL ans[N][N];

void Floyd(int x, int y) {
	memset(f, -1, sizeof f);
	for(int i = 0; i < 10; ++i) 
		f[i][(i + x) % 10] = f[i][(i + y) % 10] = 1;

	for(int k = 0; k < 10; ++k)
		for(int i = 0; i < 10; ++i)
			for(int j = 0; j < 10; ++j)
				if(f[i][k] != -1 && f[k][j] != -1) 
					f[i][j] = f[i][j] == -1 ? f[i][k] + f[k][j] : min(f[i][j], f[i][k] + f[k][j]);
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			if(f[i][j] != -1)
				f[i][j]--;
}

int main() {
	scanf("%s", s);
	int n = strlen(s);
	for(int i = 0; i < n - 1; ++i)
		ct[s[i] - '0'][s[i + 1] - '0']++;
	for(int i = 0; i < 10; ++i)
		for(int j = i; j < 10; ++j) {
			Floyd(i, j);

			bool fg = 0;
			
			for(int p = 0; p < 10; ++p)
				for(int q = 0; q < 10; ++q)
					if(ct[p][q]) {
						if(f[p][q] == -1)
							fg = 1;
						ans[i][j] += f[p][q] * ct[p][q];
					}
			if(fg)
				ans[i][j] = -1;
			ans[j][i] = ans[i][j];
		}

	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			printf("%lld%c", ans[i][j], j == 9 ? '\n' : ' ');
	return 0;
}
