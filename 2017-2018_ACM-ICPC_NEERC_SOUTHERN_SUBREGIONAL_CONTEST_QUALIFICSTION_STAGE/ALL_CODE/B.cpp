#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
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
vector <int> v[N];
map<int, int> M;
int n, a[N], b[N], f[N], st[N], sz(0), c[N];
int Que(int t) {
	int res(0);
	for(; t > 0; t -= (t & (-t))) res = max(res, st[t]);
	return res;
}
void Modify(int t, int p) {for(; t <= n; t += (t & (-t))) st[t] = max(st[t], p);}
bool cmp(const int & x, const int & y) {return x > y;}

int main() {
	//Hzy("B");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), b[i] = a[i], c[i] = a[i];
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; ++i) M[a[i]] = i;
	for(int i = 1; i <= n; ++i) b[i] = M[b[i]];
	for(int i = 1; i <= n; ++i) {
		f[i] = Que(b[i]) + 1;
		Modify(b[i], f[i]);
		v[f[i]].push_back(i);
		sz = max(sz, f[i]);
	}
	for(int i = 1; i <= sz; ++i) {		
		for(int j = 0; j < v[i].size(); ++j) printf("%d ", c[v[i][j]]);
		puts("");
	}
	return 0;
}
