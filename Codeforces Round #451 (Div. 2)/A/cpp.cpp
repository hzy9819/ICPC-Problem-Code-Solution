#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
int n;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int ed(int x) {
	int ans = 0;
	while(x) {
		ans = x % 10;
		x /= 10;
	}
	return ans;
}
int main() {
	Hzy("A");
	n = read();
	int x = n % 10;
	if(x <= 5) printf("%d\n", n - x);
	else printf("%d\n", n + 10 - x);
	return 0;
}
