#include <bits/stdc++.h>
 
using namespace std;
 
#define pie acos(-1.0) / 1010
 
const int maxn = 1007;
 
int n;
double x[maxn], y[maxn];
vector<int> G[maxn];
int f;
 
int dfs(int u, int fa) {
	for (auto v : G[u]) {
		if (v == fa) continue;
		x[v] = x[u] + cos(f * pie), y[v] = y[u] + sin(f * pie);
		f++;
		dfs(v, u);
	}
	return f + 1;
}
int main(){
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d %d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		printf("%.8f %.8f\n", x[i], y[i]);
	}
}
