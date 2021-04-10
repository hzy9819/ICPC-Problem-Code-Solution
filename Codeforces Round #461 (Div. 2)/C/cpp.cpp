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
LL n, k;
int main() {
	Hzy("C");
	n = read(), k = read();
	if(k <= 1000000) {
		for(int i = 1; i <= k; ++i)
			if(n % i != (i - 1)) {
				puts("No");
				return 0;
			}
		puts("Yes");
	}
	else puts("No");
	return 0;
}
