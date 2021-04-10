#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, x[N], y[N];
db res = 0;

void calc(int * a) {
	stack< pair<LL, int> > S;
	for(int i = 1; i <= n; ++i) {
		pair<LL, int> tmp = mk(a[i], 1);
		while(!S.empty() && S.top().l * tmp.r >= tmp.l * S.top().r) {
			pair<LL, int> t = S.top();
			S.pop();
			tmp.l += t.l, tmp.r += t.r;
		}
		S.push(tmp);
	}
	int cnt = n;
	while(!S.empty()) {
		pair<LL, int> tmp = S.top();
		S.pop();
		db t = (db) tmp.l / tmp.r;
		for(int i = tmp.r; i > 0; --i, --cnt)
			res = res + (t - a[cnt]) * (t - a[cnt]);
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		x[i] = read(), y[i] = read();
	calc(x), calc(y);
	printf("%.6lf\n", res);					
	return 0;
}
