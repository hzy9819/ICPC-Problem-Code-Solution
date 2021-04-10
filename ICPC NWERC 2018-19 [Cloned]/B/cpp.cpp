#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 400010;

struct Edge {
	int to, next;
}e[N];
int lst[N], d;

void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int a[N], f[N], n, indg[N], ans = 0;

int main() {
	n = read();
	memset(lst, -1, sizeof lst);
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		int sz = read();
		for(int j = 1; j <= sz; ++j) {
			int tmp = read();
			add(i, tmp);
			indg[tmp]++;
		}
	}
	priority_queue <pair<int, int> > Q;
	for(int i = 1; i <= n; ++i)
		if(indg[i] == 0)
			Q.push(mk(-a[i], i));
	int cnt = 1;
	while(!Q.empty()) {
		pair<int, int> t = Q.top();
		Q.pop();
		ans = max(ans, n - cnt - t.l);
		cnt++;
		for(int i = lst[t.r]; i >= 0; i = e[i].next) {
			indg[e[i].to]--;
			if(!indg[e[i].to])
				Q.push(mk(-a[e[i].to], e[i].to));
		}
	}
			
	cout << ans << endl;
	
	return 0;
}
