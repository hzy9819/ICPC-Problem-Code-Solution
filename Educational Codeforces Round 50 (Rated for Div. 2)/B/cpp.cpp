#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int q;
LL x, y, k;
int main() {
	Hzy("B");
	q = read();
	for(int i = 1; i <= q; ++i) {
		x = read(), y = read(), k = read();
		if(k < max(x, y)) puts("-1");
		else {
			if((max(x, y) - min(x, y)) & 1) cout << k - 1 << endl;
			else {
				LL t = k - max(x, y);
				if(t & 1) cout << k - 2 << endl;
				else cout << k << endl;
			}
		}
	}
	return 0;
}
