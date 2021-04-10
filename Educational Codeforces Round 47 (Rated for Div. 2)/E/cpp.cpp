#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1000010;
const LL weg = 998244353;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
LL a[N], bin[N], ans;
int main() {
	Hzy("E");
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), a[i] = (a[i] + a[i - 1]) % weg;
	bin[0] = 1;
	for(int i = 1; i <= n; ++i)
		bin[i] = bin[i - 1] * 2 % weg;
	/*for(int i = 0; i <= n; ++i)
	  bin[i] = (bin[i] - 1 + weg) % weg;*/
	ans = a[n - 1] * 2 + a[n];
	for(int i = 0; i <= n - 3; ++i)
		ans = (ans + bin[i] * (i + 5) % weg * a[n - i - 2]) % weg;
	cout << ans << endl;
	return 0;
}
