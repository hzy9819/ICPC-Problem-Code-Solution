#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, to[N], c[N], ans, now, cnt;
int vis[N];
void get_min(int s, int t) {
	if(s == t) return;
	now = min(now, c[s]);
	get_min(to[s], t);
}
void dfs(int t) {
	if(vis[t]) {
		if(vis[t] != cnt) return ;
		now = c[t];
		get_min(to[t], t);
		ans += now;
	}
	else {
		vis[t] = cnt;
		dfs(to[t]);
	}
}
int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) c[i] = read();
	for(int i = 1; i <= n; ++i) to[i] = read();
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			cnt++;
			dfs(i);
		}
	cout << ans << endl;
	return 0;
}
