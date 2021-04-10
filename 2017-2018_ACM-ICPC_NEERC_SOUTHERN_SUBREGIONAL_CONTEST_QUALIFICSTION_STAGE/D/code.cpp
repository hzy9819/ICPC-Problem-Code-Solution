#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 500010;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, t[N], a[N], b[N], st[N], sz, ans, k;
map<int, int> M;

void Modify(int t) {
	for(; t <= sz; t += (t & (-t))) st[t]++;
}

int Que(int t) {
	int res(0);
	for(; t > 0; t -= (t & (-t))) res += st[t];
	return res;
}

int main() {
	//Hzy("D");
	n = read(), k = read() - 1;
	for(int i = 1; i <= n; ++i) {
		t[i] = read();
		a[i] = t[i] - i;
		if(a[i] < 0) a[i] = 0;
		b[i] = a[i];
		a[i + n] = k - i;
		if(a[i + n] < 0) a[i + n] = 0;
		b[i + n] = a[i + n];
	}
	a[2 * n + 1] = k;
	sort(a + 1, a + 2 * n + 2);
	for(int i = 1; i <= 2 * n + 1; ++i) if(!M[a[i]]) M[a[i]] = ++sz;
	for(int i = 1; i <= n; ++i) {
		Modify(M[b[i]]);
		if(k - i < 0) break;
		ans = max(ans, Que(M[b[i + n]]));
	}
	printf("%d\n", ans);
	return 0;
}
