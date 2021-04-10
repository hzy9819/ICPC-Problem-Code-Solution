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

#define TASKNAME "generators"

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


static const int INF = 0x3fffffff;

int main() {
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));

    int n, k;
    scanf("%d%d", &n, &k);
    int sum = 0;
    int md = INF;
    int bestid = -1;
    int bestval = -1;
    vector<int> ans(n);


    for (int it = 0; it < n; it++) {
        int x0, a, b, c;
        scanf("%d%d%d%d",&x0,&a,&b,&c);
        vector<int> v(c);
        v[0] = x0;
        for (int i = 1; i < c; i++) {
            v[i] = (v[i-1] * a + b) % c;
        }
        int maxid = max_element(v.begin(), v.end()) - v.begin();
        int maxv = v[maxid];
        int nmaxv = -1;
        int nmaxvid = -1;
        sum += maxv;
        for (int i = 0; i < c; i++) {
            if ((v[i] - maxv) % k != 0) {
                if (nmaxv < v[i]) {
                    nmaxv = v[i];
                    nmaxvid = i;
                }
            }
        }
        ans[it] = maxid;
        if (nmaxv != -1) {
            if (md > maxv - nmaxv) {
                md = maxv - nmaxv;
                bestid = it;
                bestval = nmaxvid;
            }
        }
    }
    if (sum % k != 0) {
        printf("%d\n", sum);
    } else if (md != INF){
        printf("%d\n", sum - md);
        ans[bestid] = bestval;
    } else {
        printf("-1\n");
        return 0;
    }
    for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], " \n"[i == n - 1]);
    return 0;
}
