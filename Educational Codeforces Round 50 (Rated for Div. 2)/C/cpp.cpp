#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int T;
int a[30];
LL f[30][2][5];
LL S(LL s) {
	int n = 0;
	while(s) a[++n] = s % 10, s /= 10;
	memset(f, 0, sizeof f);
	f[n + 1][1][0] = 1;
	for(int i = n + 1; i > 1; --i) {
		for(int k = 0; k <= 3; ++k) {
			f[i - 1][0][k + 1] += 9 * f[i][0][k];
			f[i - 1][0][k] += f[i][0][k];
			
			if(a[i - 1]) f[i - 1][1][k + 1] += f[i][1][k];
			else f[i - 1][1][k] += f[i][1][k];
			
			if(a[i - 1]) {
				f[i - 1][0][k + 1] += (a[i - 1] - 1) * f[i][1][k];
				f[i - 1][0][k] += f[i][1][k];
			}			
		}
	}
	LL ans = f[1][0][1] + f[1][0][2] + f[1][0][3] + f[1][1][1] + f[1][1][2]+ f[1][1][3];
	return ans;
}
int main() {
	Hzy("C");
	T = read();
	LL x, y;
	for(int i = 1; i <= T; ++i) {
		cin >> x >> y;
		cout << S(y) - S(x - 1) << endl;
	}
	return 0;
}
