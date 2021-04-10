#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = (1 << 20) + 10;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int l[N], r[N], n, dis[N], ans;
queue <int> Q;

void dfs(int t) {
	if(!l[t] || !r[t]) ans = min(ans, dis[t]);
	if(l[t]) {
		dis[l[t]] = dis[t] + 1;
		dfs(l[t]);
	}
	if(r[t]) {
		dis[r[t]] = dis[t] + 1;
		dfs(r[t]);
	}
}

int main() {
	Hzy("L");
	while(cin >> n) {
		for(int i = 1; i <= n; ++i)
			scanf("%d %d", l + i, r + i);
		ans = n;
		dis[1] = 1;
		int tmp;
		while(!Q.empty()) Q.pop();
		Q.push(1) ;
		while(!Q.empty()) {
			tmp = Q.front(), Q.pop();
			if(!l[tmp] || !r[tmp]) {
				ans = dis[tmp];
				break;
			}
			if(l[tmp]) {
				dis[l[tmp]] = dis[tmp] + 1;
				Q.push(l[tmp]);
			}
			if(r[tmp]) {
				dis[r[tmp]] = dis[tmp] + 1;
				Q.push(r[tmp]);
			}
		}
		//dfs(1);
		cout << ans << endl;
	}
	return 0;
}
