#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define MOD(o) ((o) % weg)
using namespace std;
const int N = 5010;
const int weg = 998244353;

struct Edge {
	int to, nxt;
}e[N * 2];
int lst[N], d;

void add(int x, int y) {
	e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

int T[N][N], sT[N][N], f[2][N], sf[2][N], cur;
int depth[N], n, k;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void dfs(int t, int pre) {
	depth[t] = 0;
	for(int i = lst[t]; i >= 0; i = e[i].nxt)
		if(e[i].to != pre) {
			dfs(e[i].to, t);
			depth[t] = max(depth[t], depth[e[i].to] + 1);
		}
}

int D = 0;

LL F(int cur, int r) {
	if(r > D)
		return 0;
	return f[cur][r];
}

LL S(int cur, int r) {
	if(r > D)
		return sf[cur][D];
	return sf[cur][r];
}


void dp(int t, int pre) {
	for(int i = lst[t]; i >= 0; i = e[i].nxt)
		if(e[i].to != pre) 
			dp(e[i].to, t);

	cur = 0;
	f[0][0] = 1, sf[0][0] = 1;
	D = 0;

	for(int i = lst[t]; i >= 0; i = e[i].nxt)
		if(e[i].to != pre) {
			cur ^= 1;
			int nD = min(k, max(D, depth[e[i].to] + 1));
			for(int r = 0; r <= nD; ++r) {
				f[cur][r] = MOD(1LL * F(cur ^ 1, r) * sT[e[i].to][k]);
				if(r >= 1)
					f[cur][r] = MOD(0LL + f[cur][r] + 1LL * T[e[i].to][r - 1] * S(cur ^ 1, min(r - 1, k - r)));
				if(r >= 2 && k - r - 1 >= 0)
					f[cur][r] = MOD(0LL + f[cur][r] + 1LL * F(cur ^ 1, r) * sT[e[i].to][min(r - 2, k - r - 1)]);
				if(r * 2 <= k && r >= 1)
					f[cur][r] = MOD(0LL + f[cur][r] + 1LL * T[e[i].to][r - 1] * F(cur ^ 1, r));
				if(r == 0)
					sf[cur][r] = f[cur][r];
				else
					sf[cur][r] = MOD(0LL + sf[cur][r - 1] + f[cur][r]);
			}
			D = nD;
		}
	for(int i = 0; i <= D; ++i)
		T[t][i] = f[cur][i];
	sT[t][0] = T[t][0];
	for(int i = 1; i <= k; ++i)
		sT[t][i] = MOD(0LL + sT[t][i - 1] + T[t][i]);
}
					

int main() {
	n = read(), k = read();
	srand(time(0));
	int u, v, rt = rand() % n + 1;
	//rt = 6;
	memset(lst, -1, sizeof lst), d = 0;
	for(int i = 1; i < n; ++i) {
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(rt, 0);
	dp(rt, 0);
	cout << sT[rt][k] << endl;
	return 0;
}
