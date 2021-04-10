#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL Min = 0, Max = 0, n, l, r;

int main() {
	n = read(), l = read(), r = read();
	for(int i = 1, now = 1; i <= n; ++i) {
		Min += i <= l ? now : 1;
		Max += now;
		if(i < r)
			now <<= 1;
	}
	cout << Min << " " << Max; 
	return 0;
}
