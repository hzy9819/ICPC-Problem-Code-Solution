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

int t0[N], t1[N], n, a[N];
priority_queue< pair<int, int> > Q;

void Mod(int * t, int p, int w) {
	for(int i = p; i <= n; i += (i & (-i)))
		t[i] = max(t[i], w);
}

int Que(int * t, int p) {
	int tmp = 0;
	for(int i = p; i > 0; i -= (i & (-i)))
		tmp = max(t[i], tmp);
	return tmp;
}

int main() {
	int T = read();
	while(T--) {
		n = read() + 1;
		int ans = 0;
		a[1] = 1;
		t0[0] = t1[0] = t0[1] = t1[1] = 0;
		for(int i = 2; i <= n; ++i) {
			a[i] = read() + 1;
			t0[i] = t1[i] = 0;
		}
		while(!Q.empty())
			Q.pop();
		int f0, f1;
		for(int i = 1; i <= n; ++i) {
			f1 = Que(t0, a[i]) + 1;
			f0 = Que(t1, a[i]) + 1;
			f0 = max(f1, f0);
			ans = max(ans, f0);
			Mod(t0, a[i], f0);
			while(!Q.empty()) {
				pair<int, int> tmp = Q.top();
				tmp.l = -tmp.l;
				if(tmp.l <= a[i]) {
					Q.pop();
					Mod(t1, tmp.l, tmp.r + 1);
				}
				else
					break;
			}
			Q.push(mk(-a[i], f0));			
		}
		cout << ans - 1 << endl;
	}
	return 0;
}
