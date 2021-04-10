#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 4000;

struct Edge {
	int to, nxt;
}e[N * N * 2];
int lst[N], d;

void add(int x, int y) {
	e[d].to = y, e[d].nxt = lst[x], lst[x] = d++;
}

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
string s[N];
int col[N];

bool check(string a, string b) {
	if(a.size() != b.size())
		return false;
	int ct = 0;
	for(size_t i = 0; i < a.size(); ++i)
		if(a[i] != b[i])
			ct++;
	return ct == 2;
}

#define cg(t) (col[t] == 1 ? 2 : 1)

bool dfs_col(int t) {
	for(int i = lst[t]; i >= 0; i = e[i].nxt)
		if(!col[e[i].to]) {
			col[e[i].to] = cg(t);
			bool tmp = dfs_col(e[i].to);
			if(!tmp)
				return false;
		}
		else if(col[e[i].to] != cg(t))
			return false;
	return true;
}

bool color() {
	for(int i = 1; i <= n; ++i)
		if(!col[i]) {
			col[i] = 1;
			bool tmp;
			tmp = dfs_col(i);
			if(!tmp)
				return false;
		}
	return true;
}

int to[N];
bool vis[N];

bool dfs(int t) {
	for(int i = lst[t]; i >= 0; i = e[i].nxt) {
		int v = e[i].to;
		if(!vis[v]) {
			vis[v] = true;
			if(to[v] == -1 || dfs(to[v])) {
				to[v] = t;
				to[t] = v;
				return true;
			}
		}
	}
	return false;
}

int max_match() {
	int ans = 0;
	memset(to, -1, sizeof vis);
	for(int i = 1; i <= n; ++i)
		if(col[i] == 1 && to[i] == -1) {
			memset(vis, 0, sizeof vis);
			if(dfs(i))
				ans++;
		}
	return ans;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		cin >> s[i];
	memset(lst, -1, sizeof lst);
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
			if(check(s[i], s[j]))
				add(i, j), add(j, i);
	// color() ? puts("YES") : puts("NO");
	// printf("%d\n", d);
	if(!color())
		while(1);
	int mm = max_match();
	cout << n - mm << endl; 
	
	
	
	return 0;
}
