#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 1500010;
struct Node {
	int sz;
	vector <int> v;
	queue <int> q;
}a[N];
struct Edge {
	int to, next;
}e[N];
int lst[N], d, fa[N];
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}
int to[N], n, m, p;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
bool cmp(const Node & x, const Node & y) { return x.sz < y.sz ; }
vector <int> v[N];
int ans = 0;
int s[N], pre[N], nxt[N], tl;
int main() {
	Hzy("K");
	n = read(), m = read(), p = read();
	for(int i = 1; i <= m; ++i) {
		int tmp = read();
		a[i].sz = tmp;
		for(int j = 1; j <= tmp; ++j)
			a[i].v.push_back(read());
	}
	for(int i = 1; i <= p; ++i)
		a[read()].q.push(i);
	sort(a + 1, a + m + 1, cmp);
	memset(lst, -1, 4 * (m + 1));
	for(int i = 1; i <= m; ++i) {
		int tmp = a[i].sz;
		for(int j = 0; j < tmp; ++j) {
			if(to[a[i].v[j]] && fa[to[a[i].v[j]]] != i) fa[to[a[i].v[j]]] = i, add(i, to[a[i].v[j]]);
			to[a[i].v[j]] = i;
		}
	}
	for(int i = 1; i <= n; ++i)
		if(!to[i]) {
			puts("0");
			return 0;
		}
	for(int i = 1; i <= m; ++i)
		if(fa[i] == 0)
			s[++tl] = i;
	for(int i = 0; i <= m; ++i) {
		if(i != 0) pre[i] = i - 1;
		nxt[i] = i + 1;
	}
	//for(int i = 1; i <= p; ++i)
	bool fg = 1;
	while(fg) {
		ans++;
		int now = nxt[0];
		while(now <= tl) {
			if(a[s[now]].q.empty()) {
				if(lst[s[now]] == -1) {
					fg = 0;
					break;
				}
				for(int i = lst[s[now]]; i >= 0; i = e[i].next)
					s[++tl] = e[i].to;
				nxt[pre[now]] = nxt[now];
				pre[nxt[now]] = pre[now];
			}
			else {
				v[ans].push_back(a[s[now]].q.front());
				a[s[now]].q.pop();
			}
			now = nxt[now];
		}
	}
	ans--;
	cout << ans << endl;
	for(int i = 1; i <= ans; ++i) {
		cout << v[i].size() << " ";
		for(size_t j = 0; j < v[i].size(); ++j)
			printf("%d ", v[i][j]);
		puts("");
	}
	return 0;
}
