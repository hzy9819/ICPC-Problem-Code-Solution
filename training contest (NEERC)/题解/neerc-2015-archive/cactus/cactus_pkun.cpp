//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "cactus"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


vector<vector<int>> g;
vector<vector<int>> cg;
int n, m;

vector<pair<int, int>> st;
vector<int> tin;
vector<int> tup;
int timer;

void dfs0(int v, int p) {
    tin[v] = tup[v] = timer++;
    for (int u : g[v]) {
        if (u == p) continue;
        if (tin[u] > tin[v]) continue;
        st.push_back(make_pair(v, u));
        if (tin[u] != -1) {
            tup[v] = min(tup[v], tin[u]);
            continue;
        }
        dfs0(u, v);
        tup[v] = min(tup[v], tup[u]);
        if (tup[u] >= tin[v]) {
            vector<int> cycle;
            cycle.push_back(v);
            while (true) {
                auto x = st.back();
                //eprintf("(%d->%d)", x.first, x.second);
                st.pop_back();
                if (x == make_pair(v, u)) {
                    break;
                }
                cycle.push_back(x.first);
            }
            if (cycle.size() == 1)
                cycle.push_back(u);
            /*eprintf(" : ");
            for (int x : cycle)
                eprintf("%d ", x);
            eprintf("\n");*/
            if (cycle.size() == 2) {
                cg[cycle[0]].push_back(cycle[1]);
                cg[cycle[1]].push_back(cycle[0]);
            } else {
                int cid = cg.size();
                cg.push_back(cycle);
                for (int t : cycle) {
                    cg[t].push_back(cid);
                }
            }
        }
    }
}

vector<int> tid;
vector<int> tsz;
long long ans;

void dfs1(int v, int t) {
    tsz[t]++;
    tid[v] = t;
    for (int u : cg[v]) {
        //assert(0 <= u && u < tid.size());
        if (u < n && tid[u] == -1)
            dfs1(u, t);
    }
};

int dfs2(int v, int p) {
    int cur = v < n;
    for (int u : cg[v]) {
        if (u == p) continue;
        int temp = dfs2(u, v);
        cur += temp;
        if (v < n && u < n) {
            ans += temp * 1LL * (n - temp) - 1;
        }
    }
    return cur;
}

ll calc(int size) {
    return size * 1LL * (size - 1) / 2 - (size - 1);
}

int main() {
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
    scanf("%d%d", &n, &m);
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int k;
        scanf("%d", &k);
        int prev;
        scanf("%d", &prev);
        --prev;
        for (int j = 1; j < k; j++) {
            int next;
            scanf("%d", &next);
            --next;
            g[prev].push_back(next);
            g[next].push_back(prev);
            prev = next;
        }
    }
    tin.resize(n, -1);
    tup.resize(n, -1);
    cg.resize(n);
    dfs0(0, -1);

    /*for (int i = 0; i < (int)cg.size(); i++) {
        printf("%d:", i + 1);
        for (int u : cg[i])
            printf(" %d", u + 1);
        printf("\n");
    }*/
    tid.resize(n, -1);
    for (int i = 0; i < n; i++)
        if (tid[i] == -1) {
            tsz.push_back(0);
            dfs1(i, tsz.size() - 1);
        }
    dfs2(0, -1);

/*    eprintf("%lld\n", ans);

    eprintf("======\n");
    for (int sz : tsz)
        eprintf("%d\n", sz);*/

    long long sum = 0;
    for (int i = 0; i < (int)tsz.size(); i++)
        sum += calc(tsz[i]);


    for (int i = n; i < (int)cg.size(); i++) {
        long long temp = sum;
        int tot = 0;
        for (int v : cg[i]) {
            temp -= calc(tsz[tid[v]]);
            tot += tsz[tid[v]];
        }
        temp += calc(tot);
        ans += (temp - 1) * cg[i].size();
    }

    printf("%lld\n", ans);
    return 0;
}
