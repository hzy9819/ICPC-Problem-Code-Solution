#pragma comment(linker, "/STACK:256000000")


#include <iostream>
#include <tuple>
#include <sstream>
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
typedef pair<i64, i64> pi64;
typedef double ld;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

const int maxn = 51000;
vi edges;
vi e[maxn];
int vis[maxn];
set<pii> se;

int n, ec;

void add_edge(int v, int u) {
    e[v].pb(edges.size());
    edges.pb(u);
    e[u].pb(edges.size());
    edges.pb(v);
    se.insert(mp(v, u));
    se.insert(mp(u, v));
}

void pop_edge() {
    int v = edges.back();
    e[v].pop_back();
    edges.pop_back();
    int u = edges.back();
    e[u].pop_back();
    edges.pop_back();
    se.erase(mp(v, u));
    se.erase(mp(u, v));
}

int forb = -1;

void init() {
    forn(i, n) vis[i] = 0;
}

bool dfs(int v, int p, vi &st, vi &inc) {
    if (vis[v]) return true;
    vis[v] = 1;
    st.pb(v);
    inc.pb(0);
    for (int w: e[v]) {
        if (w / 2 == forb) continue;
        int u = edges[w];
        if (u == p) continue;
        if (vis[u] == 0) {
            if (!dfs(u, v, st, inc)) return false;
        } else if (vis[u] == 1) {
            int i = st.size() - 1;
            while (st[i] != u) {
                if (inc[i]) return true;
                inc[i] = 1;
                --i;
            }
        }
    }
    vis[v] = 2;
    st.pop_back();
    inc.pop_back();
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;

    freopen("cactus.in", "rt", stdin);
    freopen("cactus.out", "wt", stdout);

    int m;
    cin >> n >> m;
    ec = 0;
    forn(i, m) {
        int k;
        cin >> k;
        ec += k - 1;
        int v, u;
        cin >> v;
        --v;
        forn(i, k - 1) {
            cin >> u;
            --u;
            add_edge(u, v);
            v = u;
        }
    }
    int ans = 0;
    forn(i, ec) {
        forb = i;
        forn(u, n) forn(v, u) {
            if (se.count(mp(u, v))) continue;
            add_edge(u, v);
            init();
            vi st, inc;
            if (dfs(0, -1, st, inc) && *min_element(vis, vis + n) == 2) {
//                cerr << i << ' ' << v << ' ' << u << '\n';
                ++ans;
            }
            pop_edge();
        }
    }
    cout << ans << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
