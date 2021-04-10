#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 300010;
bool b[N];
int p[N], sz;
int n, k;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Prime() {
	for(int i = 2; i <= 300000; ++i) {
		if(!b[i]) p[++sz] = i;
		for(int j = 1; j <= sz && i * p[j] <= 300000; ++j) {
			b[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
int d[N];
int ans[N], siz;
int main() {
	Hzy("F");
	n = read(), k = read();
	Prime();
	for(int i = 1; i <= n; ++i)
		for(int j = 2 * i; j <= n; j += i)
			d[j]++;
	int tt = 0;
	for(int i = 1; i <= n; ++i) tt += d[i];
	if(tt < k) {
		puts("No");
		return 0;
	}
	for(; n > 1 && tt - d[n] > k; tt -= d[n], n--);
	siz = n;
	for(int i = 1; i <= n; ++i) ans[i] = 1;
	tt -= k;
	int tp = 0;
	for(int i = (n / 2) + 1; i <= n; ++i)
		if(!b[i]) tp++;
	if(tp >= tt) {
		for(int i = (n / 2) + 1; tt && i <= n; ++i) 
			if(!b[i]) {
				siz--, ans[i] = 0, tt--;
				if(!tt) break;
			}
	}
	else {
		for(int i = (n / 2); i >= 1; --i)
			if(!b[i]) {
				ans[i] = 0;
				tt--;
				for(int j = 2; j * i <= n; ++j)
					tt--;
				siz--;
				if(tt <= tp) break;
			}			
		for(int i = (n / 2) + 1; tt && i <= n; ++i)
			if(!b[i]) {
				siz--, ans[i] = 0, tt--;
				if(!tt) break;
			}
	}
	puts("Yes");
	printf("%d\n", siz);
	for(int i = 1; i <= n; ++i)
		if(ans[i]) printf("%d ", i);
	return 0;
}
