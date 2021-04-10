#include <bits/stdc++.h>

using namespace std;

const int maxn = 500;

int T, n, m, u, v, w;
int g[maxn][maxn];
int cases;

int main(){
	freopen("G.in", "r", stdin);
	freopen("std.out", "w", stdout);
    for (scanf("%d", &T); T; T --){
        scanf("%d%d", &n, &m);
        memset(g, 63, sizeof(g));
        for (int i = 1; i <= n; i ++)
            g[i][i] = 0;
        for (int i = 1; i <= m; i ++){
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = min(g[v][u], w);
        }
        for (int k = 1; k <= n; k ++)
            for (int i = 1; i <= n; i ++)
                for (int j = 1; j <= n; j ++)
                    g[i][j] = min(g[i][j], max(g[i][k], g[k][j]));
        int ans = 0;
        for (int i = 1; i <= n; i ++){
            int res = 0;
            for (int j = 1; j <= n; j ++)
                res += g[i][j];
            res *= i;
            ans ^= res;
        }
        printf("Case #%d: %d\n", ++cases, ans);
    }
    return 0;
}
