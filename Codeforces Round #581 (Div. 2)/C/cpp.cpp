#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
const int M = 1000010;

char c[N][N];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int f[N][N], pre[M], d[M], a[M], n, m;

vector <int> ans;

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		scanf("%s", c[i] + 1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			f[i][j] = c[i][j] == '1' ? 1 : -1;
	for(int i = 1; i <= n; ++i)
		f[i][i] = 0;
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				if(f[i][k] != -1 && f[k][j] != -1 && (f[i][j] == -1 || f[i][j] > f[i][k] + f[k][j]))
					f[i][j] = f[i][k] + f[k][j];
	m = read();
	d[0] = -1;
	for(int i = 1; i <= m; ++i) {
		a[i] = read();
		int p = 0;
		for(int j = 1; j <= n && i - j > 0; ++j)
			if(f[a[i - j]][a[i]] == j && d[i - j] != -1 &&(d[p] == -1 || d[p] > d[i - j]))
				p = i - j;
		d[i] = d[p] + 1;
		pre[i] = p;
	}

	while(m)
		ans.push_back(a[m]), m = pre[m];
	printf("%d\n", ans.size());
	for(int i = ans.size() - 1; i >= 0; --i)
		printf("%d ", ans[i]);
	
	return 0;
}
