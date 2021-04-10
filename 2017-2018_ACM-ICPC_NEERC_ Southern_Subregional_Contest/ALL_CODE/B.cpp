#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define LL long long
#define db double
#define mkp make_pair
#define fst first
#define snd second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
struct Edge {
	int to, next;
}e1[N], e2[N];
int list1[N], list2[N], d1, d2;
priority_queue <pair<int, int> > Q;
queue <int> S;
bool vis[N];
vector <int> v[N];
void add(int x, int y, int *list, int & d, Edge * e) {
	e[d].to = y, e[d].next = list[x], list[x] = d++;
}
int n, m, k;
int ans[N], Min[N], din[N], dout[N], d[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Imps() {
	puts("-1");
	exit(0);
}
void Delete(int x) {
	int y;
	for(int i = list2[x]; i >= 0; i = e2[i].next) {
		y = e2[i].to;
		d[y]--;
		if(!d[y] && !ans[y]) Q.push(mkp(Min[y], y));
	}
}
int main() {
	Hzy("B");
	n = read(), m = read(), k = read();
	memset(list1, -1, 4 * (n + 1)), memset(list2, -1, 4 * (n + 1));
	for(int i = 1; i <= n; ++i) ans[i] = read(), vis[ans[i]] = 1, v[ans[i]].push_back(i);
	int x, y;
	pair<int, int> tmp;
	for(int i = 1; i <= m; ++i) {
		x = read(), y = read();
		add(y, x, list1, d1, e1);
		add(x, y, list2, d2, e2);
		din[x]++, dout[y]++;
	}
	for(int i = 1; i <= n; ++i) {
		d[i] = din[i];
		if(!d[i]) S.push(i);
	}
	while(!S.empty()) {
		x = S.front(), S.pop();
		if(ans[x]) {
			if(ans[x] < Min[x]) Imps();
			else Min[x] = ans[x];
		}
		else if(!Min[x]) Min[x] = 1;
		for(int i = list1[x]; i >= 0; i = e1[i].next) {
			y = e1[i].to;
			Min[y] = max(Min[y], Min[x] + 1);
			d[y]--;
			if(!d[y]) S.push(y);
		}
	}
	for(int i = 1; i <= n; ++i) {
		d[i] = dout[i];
		if(!d[i] && !ans[i]) Q.push(mkp(Min[i], i));
	}
	for(int i = k; i >= 1; --i) {
		for(int j = 0; j < v[i].size(); ++j) {
			x = v[i][j];
			Delete(x);
		}
		while(!Q.empty()) {
			tmp = Q.top();
			if(tmp.fst > i) Imps();
			else if(tmp.fst == i) ans[tmp.snd] = i, vis[i] = 1, Q.pop(), Delete(tmp.snd);
			else break;
		}
		if(!vis[i]) {
			if(!Q.empty()) {
				tmp = Q.top();
				ans[tmp.snd] = i, vis[i] = 1, Q.pop(), Delete(tmp.snd);
			}
			else Imps();
		}
	}
	for(x = 1; x <= n; ++x)
		for(int i = list1[x]; i >= 0; i = e1[i].next)
			if(ans[x] >= ans[e1[i].to]) Imps();
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	return 0;
}
