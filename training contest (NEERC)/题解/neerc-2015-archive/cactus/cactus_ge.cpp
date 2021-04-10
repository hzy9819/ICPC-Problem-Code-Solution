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
const int size = 200 * 1000 + 100;

vector <pair <int, int> > edges;

vector <pair <int, int> > vertex[size];

int n, m;
vector <vector <int> > cycles;
vector <pair <int, int> > stk;
bool used[size];
bool notree[size];
bool nocycle[size];
int subsz[size];
vector <int> vis;
int mycomp[size];

void dfs3(int v) {
	used[v] = true;
	vis.pb(v);

	for (int i = 0; i < (int) vertex[v].size(); i++)
		if (!used[vertex[v][i].fs] && !nocycle[vertex[v][i].sc])
			dfs3(vertex[v][i].fs);
}

void dfs2(int v, int from) {
	subsz[v] = 1;
	for (int i = 0; i < (int) vertex[v].size(); i++) {
		if (vertex[v][i].fs == from || notree[vertex[v][i].sc])
			continue;

		dfs2(vertex[v][i].fs, v);
		subsz[v] += subsz[vertex[v][i].fs];
	}

//	cerr << v << ' ' << subsz[v] << endl;
}

void dfs(int v, int from) {
//    cerr << v << ' ' << from << endl;
	used[v] = true;
	stk.pb(mp(v, from));

	for (int i = 0; i < (int) vertex[v].size(); i++) {
		if (vertex[v][i].sc == from || nocycle[vertex[v][i].sc])
			continue;	
		if (!used[vertex[v][i].fs]) {
			dfs(vertex[v][i].fs, vertex[v][i].sc);
		} else {
//			cerr << "CYCLE" << v << ' ' << vertex[v][i].fs << ' ' << vertex[v][i].sc << ' ' << nocycle[vertex[v][i].sc] << endl;

			vector <int> cyc;
			cyc.pb(vertex[v][i].fs);
			notree[vertex[v][i].sc] = true;
			nocycle[vertex[v][i].sc] = true;

			int p = (int) stk.size() - 1;
			while (stk[p].fs != vertex[v][i].fs) {
				cyc.pb(stk[p].fs);
				nocycle[stk[p].sc] = true;

				p--;
			}

			cycles.pb(cyc);
		}
	}

	stk.pop_back();
}

int main() {
    freopen("cactus.in", "r", stdin);
    freopen("cactus.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
    	int len;
    	scanf("%d", &len);

    	int lst;
    	scanf("%d", &lst);
    	lst--;
    	for (int i = 0; i < len - 1; i++) {
    		int cur;
    		scanf("%d", &cur);
    		cur--;

    		edges.pb(mp(lst, cur));
    		lst = cur;
    	}
    }

    int cnt = 0;
    for (int i = 0; i < (int) edges.size(); i++) {
    	//num[edges[i]] = cnt;
    	vertex[edges[i].fs].pb(mp(edges[i].sc, cnt));
    	vertex[edges[i].sc].pb(mp(edges[i].fs, cnt));
    	
    	cnt++;
    }

    dfs(0, -1);

    //for (int i = 0; i < (int) edges.size(); i++)  {
    //	cerr << edges[i].fs << ' ' << edges[i].sc << ' ' << notree[i] << ' ' << nocycle[i] << endl;
    //}

    long long ans = 0;

    dfs2(0, -1);
    for (int i = 0; i < (int) edges.size(); i++) {
    	if (!nocycle[i]) {
    		int h = min(subsz[edges[i].fs], subsz[edges[i].sc]);

//    		cerr << h * 1ll * (n - h) - 1ll << endl;
    		ans += h * 1ll * (n - h) - 1ll;
    	}
    }

    for (int i = 0; i < n; i++)
    	used[i] = false;
    long long help = 0;
    for (int i = 0; i < n; i++)
    	if (!used[i]) {
    		vis.clear();
    		dfs3(i);

    		for (int j = 0; j < (int) vis.size(); j++)
    			mycomp[vis[j]] = vis.size();

    		int h = vis.size();
    		help += (h - 2) * 1ll * (h - 1) / 2;	
    	}

    //for (int i = 0; i < n; i++)
    //	cerr << i << ' ' << mycomp[i] << endl;

    for (int i = 0; i < (int) cycles.size(); i++) {
    	int total = 0;
    	for (int j = 0; j < (int) cycles[i].size(); j++) {
    //		cerr << "cycle " << i << ' ' << cycles[i][j] << endl;
    		total += mycomp[cycles[i][j]];
    		int h = mycomp[cycles[i][j]];
    		help -= (h - 2) * 1ll * (h - 1) / 2;
    	}

    	//cerr << total << endl;
    	help += (total - 2) * 1ll * (total - 1) / 2 - 1;
    	ans += help * (long long) cycles[i].size();

    	help -= (total - 2) * 1ll * (total - 1) / 2 - 1;

    	for (int j = 0; j < (int) cycles[i].size(); j++) {
    		int h = mycomp[cycles[i][j]];
    		help += (h - 2) * 1ll * (h - 1) / 2;
    	}
    }

    cout << ans << endl;

    return 0;
}