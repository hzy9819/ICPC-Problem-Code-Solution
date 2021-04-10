#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 300010;
const int INF = 1e9;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
LL f[N], h[N], b[N], t[N];
bool vis[N];

stack <int> S;

priority_queue < pair<LL, int> > Q;

LL Que(int x) {
	LL res = -INF;
	if(x == 0)
		res = 0, x = 1;
	for(int i = x; i <= n; i += (i & (-i)))
		res = max(res, t[i]);
	return res;
}

void Mod(int x, LL d) {
	for(int i = x; i > 0; i -= (i & (-i)))
		t[i] = max(t[i], d);
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		h[i] = read(), t[i] = -INF;
	for(int i = 1; i <= n; ++i)
		b[i] = read();
	for(int i = 1; i <= n; ++i) {
		int tmp;
		LL temp;
		while(!S.empty() && h[i] < h[S.top()]) {
			tmp = S.top();
			vis[tmp] = 0;
			S.pop();
		}
		if(!S.empty()) 
			tmp = S.top();
		else
			tmp = 0;
		temp = Que(tmp);
		temp += b[i];
		vis[i] = 1;
		S.push(i);
		Q.push(mk(temp, i));
		while(!Q.empty() && !vis[Q.top().r])
			Q.pop();
		f[i] = Q.top().l;
		Mod(i, f[i]);
	}
	cout << f[n] << endl;
	return 0;
}
