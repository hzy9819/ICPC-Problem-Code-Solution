#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 500010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

struct Node {
	int sz, v[3], son[4];
	void clear() {
		v[0] = v[1] = v[2] = 0;
		son[0] = son[1] = son[2] = son[3] = 0;
	}
}a[N];
int cnt = 0, n, rt;

void Update(int & t) {
	if(a[t].sz == 3) {
		cnt++;
		a[cnt].clear();
		a[cnt].sz = 1, a[cnt].v[0] = a[t].v[2], a[cnt].son[0] = a[t].son[2], a[cnt].son[1] = a[t].son[3];
		cnt++;
		a[cnt].clear();
		a[cnt].sz = 1, a[cnt].v[0] = a[t].v[1], a[cnt].son[0] = t, a[cnt].son[1] = cnt - 1;
		a[t].sz = 1;
		t = cnt;
	}
}

bool Insert(int & t, int v) {
	if(t == 0) {
		t = ++cnt;
		a[cnt].clear();
		a[t].sz = 1, a[t].v[0] = v, a[t].son[0] = a[t].son[1] = 0;
		return 1;
	}
	else if(a[t].sz == 3)
		return 0;
	else if(a[t].son[0]) {
		while(1) {
			int i = 0, j;
			while(i < a[t].sz && a[t].v[i] < v)
				++i;
			int tmp = a[t].son[i];
			if(!Insert(tmp, v)) {
				for(j = a[t].sz; j > i; --j)
					a[t].v[j] = a[t].v[j - 1];
				a[t].sz++;
				for(j = a[t].sz; j > i; --j)
					a[t].son[j] = a[t].son[j - 1];

				int temp = ++cnt;
				a[cnt].clear();
				a[temp].sz = 1, a[temp].v[0] = a[tmp].v[2], a[temp].son[0] = a[tmp].son[2], a[temp].son[1] = a[tmp].son[3];
				a[tmp].sz = 1;
				a[t].v[i] = a[tmp].v[1];
				a[tmp].son[i] = temp;
				swap(a[t].son[i], a[t].son[i + 1]);
			}
			else break;
		}
		return 1;
	}
	else {
		int i = 0;
		while(i < a[t].sz && a[t].v[i] < v)
			i++;
		for(int j = a[t].sz; j > i; --j)
			a[t].v[j] = a[t].v[j - 1];
		a[t].sz++;
		a[t].son[a[t].sz] = 0, a[t].v[i] = v;
		return 1;
	}
}

void dfs(int t) {
	if(!t) return;
	for(int i = 0; i < a[t].sz; ++i) {
		if(i)
			printf(" ");
		printf("%d", a[t].v[i]);
	}
	puts("");
	for(int i = 0; i <= a[t].sz; ++i)
		dfs(a[t].son[i]);
}

int main() {
	int T = read(), cas = 0;
	while(T--) {
		++cas;
		n = read();
		cnt = rt = 0;
		for(int i = 0; i < n; ++i) {
			int x = read();
			while(!Insert(rt, x))
				Update(rt);
		}
		printf("Case #%d:\n", cas);
		dfs(rt);
	}
	return 0;
}
