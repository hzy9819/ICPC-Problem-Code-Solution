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

#define TASKNAME "J"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");

int request();

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


const int MAXN = 1001;
char q[MAXN];

char eq[MAXN];
int n;

int request(char* q) {
    printf("%s\n", q);
    fflush(stdout);
    int result;
    scanf("%d", &result);
    if (result == n) {
        exit(0);
    }
    return result;
}


int main() {
    scanf("%d", &n);
    while (true) {
        for (int i = 0; i < n; i++) {
            q[i] = rand() % 2 + '0';
        }
        int result = request(q);
        if (result == n / 2) {
            break;
        }
    }

    eq[0] = q[0];
    for (int i = 1; i < n; i++) {
        q[0] ^= 1;
        q[i] ^= 1;
        eq[i] = (request(q) == n / 2) + '0';
        q[0] ^= 1;
        q[i] ^= 1;
        if (q[i] == '1') {
            eq[i] ^= 1;
        }
    }

    request(eq);
    for (int i = 0; i < n; i++) {
        eq[i] ^= 1;
    }
    request(eq);
    assert(0);
    return 0;
}
