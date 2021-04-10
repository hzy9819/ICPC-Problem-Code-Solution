#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <time.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
const int N = 1000050;
vector <int> go[N], gi[N];
int a[N], b[N];
bool vis[N];
int n, m, st;
clock_t bg;
void Out() {
	for(int i = 0; i < n; ++i)
		if(a[i] == 0) {
			for(int j = i; j < n; ++j)
				printf("%d ", a[j] + 1);
			for(int j = 0; j < i; ++j)
				printf("%d ", a[j] + 1);
			puts("1");
			break;
		}
	//for(int i = 0; i < n; ++i)
	//	printf("%d ", a[i] + 1);
	exit(0);
}
void IMP() {
	puts("There is no route, Karl!");
	exit(0);
}
inline void dfs(int t, int sum) {
	if (sum == n) Out();
	if(clock() - bg > 1980) IMP();
	if (0 < sum && sum < n && t == st) return;
	for (size_t j = 0; j < go[t].size(); j++) {
		int u = go[t][j];
		if (!vis[u]) {
			vis[u] = true;
			a[sum + 1] = u;
			dfs(u, sum + 1);
			vis[u] = false;
		}
	}
}

int main() {
	Hzy("king");
	srand(time(0));
	bg = clock();
	n = read(), m = read();
	for (int i = 0; i < n; i++) {
		go[i].clear();
		gi[i].clear();
	}
	for (int i = 0; i < m; i++) {
		//scanf("%d %d", a + i, b + i);
		a[i] = read(), b[i] = read();
		a[i]--; b[i]--;
		go[a[i]].push_back(b[i]);
		gi[b[i]].push_back(a[i]);
	}
    for (int i = 0; i < n; i++) {
		if (go[i].size() == 1) {
			int u = go[i][0];
			for (size_t j = 0; j < gi[u].size(); j++) {
				int v = gi[u][j];
				if (v != i) 
					go[v].erase(find(go[v].begin(), go[v].end(), u));
			}
			gi[u].resize(1);
			gi[u][0] = i;
		}
    } //use to clear same edges

	
	for (int i = 0; i < n; i++) {
		if (go[i].empty() || gi[i].empty()) {
			IMP();
			//return 0;
		}
		else
			random_shuffle(go[i].begin(), go[i].end());
	}
	
	//for (int i = 0; i < n; i++) vis[i] = false;
	st = rand() % n;
	a[0] = st;
	dfs(st, 0);
	IMP();
	return 0;
}
