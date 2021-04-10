#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
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
int n;
LL a[N], ans;
bool f1, f2;
int now;
int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		if(a[i] >= 0) f1 = 1;
		if(a[i] <= 0) f2 = 1;
	}
	if(n == 1) {
		cout << a[1] << endl;
		return 0;
	}
	now = 1;
	for(int i = 2; i <= n; ++i)
		if(a[i] < a[now]) now = i;

	for(int i = 1; i <= n; ++i)
		if(i != now) ans += abs(a[i]);

	if(f1) ans -= a[now];
	else ans += a[now];

	cout << ans << endl;
	
	return 0;
}
