#include<cstdio>
#include<cstring>
#include<map>
#include<set>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
#define pb push_back
#define sz(x) ((int)(x).size())
#define rep(i,l,r) for(int i=(l);i<(r);++i)
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 7;
const int INF = 2e9 + 7;
const int MOD = 1e9 + 7;
//--------head--------
void inc(int &x, int y) {
    x += y;
    if (x >= MOD)
        x -= MOD;
}
int S, cod[20], col[20];
void decode(int a[], int n, int st) {
    for (int i = n; i >= 0; --i, st >>= 3)
        a[i] = st & 7;
}
int encode(int a[], int n) {
    int id = 0, st = 0;
    memset(col, -1, sizeof(col)), col[0] = 0;
    for (int i = 0; i <= n; ++i) {
        if (col[a[i]] == -1)
            col[a[i]] = ++id;
        a[i] = col[a[i]];
        st = (st << 3) | a[i];
    }
    return st;
}
struct Hash {
    const static int H = 1e4 + 7, N = 5e6 + 7;
    int n, nxt[N], head[H];
    int st[N], w[N], d[N];
    void init() {
        n = 0, memset(head, -1, sizeof(head));
    }
    void ins(int _st, int _w, int _d) {
        int p = _st % H;
        for (int i = head[p]; ~i; i = nxt[i])
            if (st[i] == _st) {
                if (_w < w[i]) {
                    w[i] = _w, d[i] = _d;
                } else if (_w == w[i]) {
                    inc(d[i], _d);
                }
                return ;
            }
        st[n] = _st, w[n] = _w, d[n] = _d;
        nxt[n] = head[p], head[p] = n++;
    }
    void out() {
        for (int p = 0; p < H; ++p)
            for (int i = head[p]; ~i; i = nxt[i]) {
                decode(cod, S, st[i]);
                rep(j, 0, S + 1)
                    printf("%d", cod[j]);
                printf("(%d) %d %d\n", st[i], w[i], d[i]);
            }
    }
} hs[2];
int n, m, v[807][8], h[807][8];
void blank(int x, int y, int t) {
    rep(i, 0, hs[t].n) {
        decode(cod, S, hs[t].st[i]);
        int U = cod[y], flag = 0;
        if (x == 0)
            flag = 1;
        else if (U > 0) {
            rep(j, 0, m)
                if (j != y && cod[j] == U) {
                    flag = 1;
                    break;
                }
        }
        if (x > 0 && U > 0) {
            hs[t ^ 1].ins(hs[t].st[i], hs[t].w[i] + v[x][y], 
                2ll * hs[t].d[i] % MOD);
        }
        if (y > 0 && flag) {
            decode(cod, S, hs[t].st[i]);
            cod[y] = cod[y - 1];
            hs[t ^ 1].ins(encode(cod, S), hs[t].w[i] + h[x][y],
                2ll * hs[t].d[i] % MOD);
        }
        if (flag) {
            decode(cod, S, hs[t].st[i]);
            cod[y] = 14;
            hs[t ^ 1].ins(encode(cod, S), hs[t].w[i], hs[t].d[i]);
        }
        if (x > 0 && y > 0 && cod[y - 1] != U) {
            decode(cod, S, hs[t].st[i]);
            int L = cod[y - 1];
            rep(j, 0, m)
                if (cod[j] == U)
                    cod[j] = L;
            hs[t ^ 1].ins(encode(cod, S), hs[t].w[i] + v[x][y] + h[x][y], 
                3ll * hs[t].d[i] % MOD);    
        }
    }
}
int main() {
	freopen("E.in", "r", stdin), freopen("E.out", "w", stdout);
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d", &n, &m), S = m - 1;
        rep(i, 0, n)
            rep(j, 1, m)
                scanf("%d", &h[i][j]);
        rep(i, 1, n)
            rep(j, 0, m)
                scanf("%d", &v[i][j]);
        int t = 0;
        hs[t].init();
        hs[t].ins(0, 0, 1);
        rep(i, 0, n)
            rep(j, 0, m) {
                t ^= 1;
                hs[t].init();
                blank(i, j, t ^ 1);
            }
        fill_n(cod, m, 1);
        int st = encode(cod, S);
        int mst = -1, deg = -1;
        rep(i, 0, hs[t].n)
            if (hs[t].st[i] == st)        
                mst = hs[t].w[i], deg = hs[t].d[i];
        printf("Case #%d: %d %d\n", cas + 1, mst, deg);
    }
    return 0;
}
