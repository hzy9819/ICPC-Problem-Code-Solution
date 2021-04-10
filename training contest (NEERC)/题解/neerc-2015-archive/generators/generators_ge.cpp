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
const int len = 1010;
const int inf = 1000 * 1000 * 1000;

int n, k;

pair <pair <int, int>, pair <int, int> > gen(int x, int a, int b, int c) {
	vector <pair <int, int> > elements;

	for (int i = 0; i < len; i++) {
		elements.pb(mp(x, i));
		x = (a * x + b) % c;
	}

	pair <int, int> b1, b2;
	b1 = mp(0, -1);
	b2 = mp(0, -1);

	for (int i = 0; i < (int) elements.size(); i++) {
		if (elements[i] > b1) {
			b1 = elements[i];
		}
	}
	for (int i = 0; i < (int) elements.size(); i++) {
		if (elements[i].fs % k != b1.fs % k && elements[i] > b2)
			b2 = elements[i]; 
	}

	return mp(b1, b2);
}

int main() {
    freopen("generators.in", "r", stdin);
    freopen("generators.out", "w", stdout);

    vector <pair <pair <int, int>, pair <int, int> > > vars;

    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
    	int x, a, b, c;
    	scanf("%d%d%d%d", &x, &a, &b, &c);

    	vars.pb(gen(x, a, b, c));
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    	ans += vars[i].fs.fs;
    if (ans % k != 0) {
    	printf("%d\n", ans);
    	for (int i = 0; i < n; i++) {
    		printf("%d%c", vars[i].fs.sc, " \n"[i == n - 1]);
    	}
    } else {
    	int p = -1;
    	int dif = inf;
    	for (int i = 0; i < n; i++) {
    		if (vars[i].sc.sc != -1 && vars[i].fs.fs - vars[i].sc.fs < dif) {
    			dif = vars[i].fs.fs - vars[i].sc.fs;
    			p = i;
    		}
    	}

    	if (p == -1) {
    		printf("-1\n");
    		return 0;
    	}

    	printf("%d\n", ans - dif);
    	for (int i = 0; i < n; i++) {
    		if (p == i)
    			printf("%d%c", vars[i].sc.sc, " \n"[i == n - 1]);
    		else
	   			printf("%d%c", vars[i].fs.sc, " \n"[i == n - 1]);	
    	}	
    }

    return 0;
}