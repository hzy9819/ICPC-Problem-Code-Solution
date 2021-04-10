#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 5010;
char s[N][N], now[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, k, sz[N][200];
bool f = 0;
bool check() {
	int tmp;
	for(int i = 1; i <= n; ++i) {
		tmp = 0;
		for(int j = 1; j <= k; ++j) if(now[j] != s[i][j]) tmp++;
		if(tmp > 2) return 0;
		if(tmp == 0 && !f) return 0;
	}
	return 1;
}
int main() {
	Hzy("E");
	scanf("%d %d\n", &n, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%s", s[i] + 1);
	/*if(k == 1) {
		for(int i = 2; i <= n; ++i)
			if(s[i][1] != s[1][1]) {
				puts("-1");
				return 0;
			}
		printf("%c", s[1][1]);
		return 0;
		}*/					 
	for(int i = 1; i <= k; ++i) now[i] = s[1][i];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= k; ++j) sz[i][s[i][j]]++;
	for(int i = 2; i <= n; ++i)
		for(int j = 'a'; j <= 'z'; ++j) {
			if(sz[1][j] >= 2) f = 1;
			if(sz[1][j] != sz[i][j]) {
				puts("-1");
				return 0;
			}
		}
	bool fg = 0;
	if(check()) fg = 1;
	if(!fg) {
		for(int i = 1; i <= k; ++i)
			for(int j = i + 1; j <= k; ++j)
				if(now[i] != now[j]) {
					swap(now[i], now[j]);
					if(check()) {
					fg = 1;
					break;
					}
					swap(now[i], now[j]);
				}
	}
	if(!fg) puts("-1");
	else for(int i = 1; i <= k; ++i) printf("%c", now[i]);
	return 0;
}
