#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100;


int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int a[N][N], n, m, b[N][N];

vector<pair<int, int> > ans;

bool Try(int x, int y, int dx, int dy) {
	return a[x][y] && a[x + dx][y] && a[x][y + dy] && a[x + dx][y + dy];
}

int dx[] = {-1, -1, 1, 1};
int dy[] = {1, -1, 1, -1};

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			a[i][j] = read();
	bool fg = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			if(!a[i][j] && b[i][j])
				fg = 1;
			else if(a[i][j] && !b[i][j]) {
				bool flg = 0;
				for(int k = 0; k < 4; ++k)
					if(Try(i, j, dx[k], dy[k])) {
						flg = 1;
						b[i][j] = b[i + dx[k]][j] = b[i][j + dy[k]] = b[i + dx[k]][j + dy[k]] = 1;
						ans.push_back(mk(i - (dx[k] == -1), j - (dy[k] == -1)));
						break;
					}
				if(!flg)
					fg = 1;
			}
	if(fg)
		puts("-1");
	else {
		cout << ans.size() << endl;
		for(size_t i = 0; i < ans.size(); ++i)
			cout << ans[i].l << " " << ans[i].r << endl;
	}
	return 0;
}
