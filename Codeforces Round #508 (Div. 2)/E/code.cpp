#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <time.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 110;
clock_t bg;
struct Node {
	int a, b, c;
	bool operator < (const Node & p) {
		return c < p.c;
	}
}a[N];
int n, ans, now;
bool vis[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

vector <int> v[5];

void dfs(int col) {
	ans = max(ans, now);
	if(clock() - bg > 1950) {
		cout << ans << endl;
		exit(0);
	}
	for(int i = 0; i < v[col].size(); ++i) {
		int t = v[col][i];
		if(!vis[t]) {
			vis[t] = 1;
			now += a[t].c;
			if(a[t].a == col) dfs(a[t].b);
			else dfs(a[t].a);
			now -= a[t].c;
			vis[t] = 0;
		}
	}
}

int main() {
	Hzy("E");
	bg = clock();
	n = read();
	for(int i = 1; i <= n; ++i) 
		a[i].a = read(), a[i].c = read(), a[i].b = read();

	random_shuffle(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i) {
		v[a[i].a].push_back(i);
		if(a[i].a != a[i].b) v[a[i].b].push_back(i);
	}
	
	for(int i = 1; i <= n; ++i) {
		vis[i] = 1;
		now = a[i].c;
		dfs(a[i].a);
		dfs(a[i].b);
		vis[i] = 0;
	}

	cout << ans << endl;
	
	return 0;
}
