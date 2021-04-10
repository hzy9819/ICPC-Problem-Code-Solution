#pragma comment(linker, "/STACK:1000000000")
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);


int main() {
    freopen("adjustment.in", "r", stdin);
    freopen("adjustment.out", "w", stdout);

    int n, q;
    scanf("%d%d", &n, &q);

    long long sumr = 0, sumc = 0;
    int cntr = 0, cntc = 0;

    set <int> rows, cols;

    for (int i = 0; i < q; i++) {
    	char tp;
    	int p;

    	scanf(" %c%d", &tp, &p);

    	if (tp == 'R') {
    		if (rows.find(p) != rows.end()) {
    			printf("0\n");
    			continue;
    		}

    		rows.insert(p);
    		long long ans = p * 1ll * (n - cntc) + (n + 1) * 1ll * n / 2;
    		printf("%lld\n", ans - sumc);

    		sumr += p;
    		cntr++;
    	} else {
    	   	if (cols.find(p) != cols.end()) {
    			printf("0\n");
    			continue;
    		}

    		cols.insert(p);

    		long long ans = p * 1ll * (n - cntr) + (n + 1) * 1ll * n / 2;
    		printf("%lld\n", ans - sumr);

    		sumc += p;
    		cntc++;
    	}
    }

    return 0;
}