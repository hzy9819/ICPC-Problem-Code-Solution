#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
const db PI = acos(-1.);

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

pair <db, db> p[N];
int n, cnt = 0;
vector <int> v[N];
db PI_p;

void dfs(int t, int pre/*, db L, db R*/) {
	/*int Sz = v[t].size();
	if(pre != 0)
		Sz--;
	if(!Sz)
	return ;*/
	//db len = (R - L) / Sz;
	//int cnt = 0;
	for(size_t i = 0; i < v[t].size(); ++i)
		if(v[t][i] == pre)
			continue;
		else {
			//cnt++;
			//db sL = L + len * (cnt - 1), sR = L + len * cnt;
			//db mid = (sL + sR) / 2;
			p[v[t][i]] = mk(p[t].l + cos(PI_p * cnt), p[t].r + sin(PI_p * cnt));
			cnt++;
			dfs(v[t][i], t);
		}
}

int main() {
	n = read();
	for(int i = 1; i < n; ++i) {
		int x, y;
		x = read(), y = read();
		v[x].push_back(y), v[y].push_back(x);
	}
	PI_p = PI / n;
	srand(time(0));
	int rt = rand() % n + 1;
	//int rt = 1;
	p[rt] = mk(0, 0);
	dfs(rt, 0);

	for(int i = 1; i <= n; ++i)
		printf("%.7lf %.7lf\n", p[i].l, p[i].r);
	
	return 0;
}
