#pragma comment(linker, "/STACK:256000000")

#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

const int maxn = 210000;

int n;
vi e[maxn];
int vis[maxn], w[maxn];
int tin[maxn], up[maxn];

int T;

vvi cycles;
vi st;

int par[maxn], sz[maxn];

int root(int v) {
    return v == par[v] ? v : par[v] = root(par[v]);
}

void unite(int x, int y) {
    x = root(x); y = root(y);
    par[x] = y;
    sz[y] += sz[x];
}

i64 ans = 0;

void dfs(int v, int p) {
//    cerr << v << ' ' << p << ' ' << T << '\n';
    if (vis[v]) return;
    vis[v] = 1;
    st.pb(v);
    tin[v] = up[v] = T++;
    w[v] = 1;
    for (int u: e[v]) {
        if (u == p) continue;
        if (vis[u] == 0) {
            dfs(u, v);
            w[v] += w[u];
            uin(up[v], up[u]);
            if (up[u] > tin[v]) {
//                cerr << "bridge: " << u << ' ' << v << '\n';
                unite(u, v);
                ans += 1LL * w[u] * (n - w[u]);
            }
        } else if (vis[u] == 1) {
            uin(up[v], tin[u]);
            vi cycle;
            cycle.pb(u);
            for (int i = st.size() - 1; st[i] != u; --i) {
                cycle.pb(st[i]);
            }
            cycles.pb(cycle);
        }
    }
    st.pop_back();
    vis[v] = 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;

    freopen("cactus.in", "rt", stdin);
    freopen("cactus.out", "wt", stdout);

    int m, ec = 0;
    cin >> n >> m;
    forn(i, m) {
        int k;
        cin >> k;
        ec += k - 1;
        int v;
        cin >> v; --v;
        forn(j, k - 1) {
            int u;
            cin >> u; --u;
            e[v].pb(u);
            e[u].pb(v);
            v = u;
        }
    }
    forn(i, n) par[i] = i, sz[i] = 1;
//    cerr << "dfs:";
    dfs(0, -1);
//    cerr << "done\n";
    i64 tc2 = 0;
    forn(i, n) {
        if (i == par[i]) tc2 += 1LL * sz[i] * (sz[i] - 1) / 2 - (sz[i] - 1);
    }
    for (vi &cycle: cycles) {
        i64 c2 = tc2;
        int csz = 0;
        for (int v: cycle) {
//            cerr << v << ' ';
            int vsz = sz[root(v)];
            c2 -= 1LL * vsz * (vsz - 1) / 2 - (vsz - 1);
            csz += vsz;
        }
//        cerr << '\n';
//        cerr << csz << ' ' << c2 << ' ' << (i64)cycle.size() * (c2 + 1LL * csz * (csz - 1) / 2 - (csz - 1)) << '\n';
        ans += (i64)cycle.size() * (c2 + 1LL * csz * (csz - 1) / 2 - (csz - 1));
    }
    cout << ans - ec << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
