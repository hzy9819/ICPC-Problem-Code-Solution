#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define LL long long
#define db double
#define mk(x, y) make_pair(x, y)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 300010;
const int Lim = 300000;
int gcd(int a, int b) {
	if(a < b) swap(a, b);
	int c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}
int n;
int a[N];
bool vis[N];
vector <int> st, v;
set <pair<int, int> > S;
struct Edge {
	int to, next;
}e[N * 20];
int lst[N], d;
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
	if(d > N * 20) exit(0);
}
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int dis[N];
queue <int> Q;
bool inq[N];
void Spfa(int * lst, Edge * e, int * dis, int s) {
	for(int i = 1; i <= Lim; ++i) dis[i] = -1;
	Q.push(s), dis[s] = 0, inq[s] = 1;
	while(!Q.empty()) {
		int tmp = Q.front();
		inq[tmp] = 0, Q.pop();
		for(int i = lst[tmp]; i >= 0 ; i = e[i].next)
			if(dis[e[i].to] == -1 || dis[e[i].to] > dis[tmp] + 1) {
				dis[e[i].to] = dis[tmp] + 1;
				if(!inq[e[i].to]) {
					Q.push(e[i].to);
					inq[e[i].to] = 1;
				}
			}
	}
}
int main() {
	Hzy("F");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		if(!vis[a[i]]) {
			st.push_back(a[i]);
			v.push_back(a[i]);
			vis[a[i]] = 1;
			for(int j = 2; j * a[i] <= Lim; ++j)
				vis[j * a[i]] = 1;
		}
	memset(lst, -1, sizeof lst);
	for(size_t i = 0; i < v.size(); ++i)
		for(size_t j = 1; j < st.size(); ++j) {
			int tmp = gcd(v[i], st[j]);
			if(S.find(mk(tmp, v[i])) != S.end()) continue;
			if(!vis[tmp]) vis[tmp] = 1, v.push_back(tmp);
			S.insert(mk(tmp, v[i]));
			add(tmp, v[i]);
		}
	if(!vis[1]) return puts("-1"), 0;
	Spfa(lst, e, dis, 1);
	int ans = n + 1;
	for(size_t i = 0; i < st.size(); ++i)
		if(dis[st[i]] != -1 && dis[st[i]] < ans) ans = dis[st[i]];
	if(ans == n + 1) puts("-1");
	else printf("%d\n", ans + 1); 
	return 0;
}
