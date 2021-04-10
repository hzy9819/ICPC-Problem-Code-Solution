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
const int N = 1000010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, q, x;
char c;
bool b1[N], b2[N];
LL s1, s2, n1, n2;
int main() {
	Hzy("adjustment");
	n = read(), q = read();
	LL ans;
	for(int i = 1; i <= q; ++i) {
		scanf("%c", &c);
		x = read();
		if(c == 'R') {
			if(!b1[x]) {
				ans = x * (n - n1) + n * (n + 1) / 2 - s1;
				b1[x] = 1, s2 += x, n2++;
			}
			else ans = 0;
		}
		else {
			if(!b2[x]) {
				ans = x * (n - n2) + n * (n + 1) / 2 - s2;
				b2[x] = 1, s1 += x, n1++;
			}
			else ans = 0;
		}
		cout << ans << endl;
	}			
	return 0;
}
