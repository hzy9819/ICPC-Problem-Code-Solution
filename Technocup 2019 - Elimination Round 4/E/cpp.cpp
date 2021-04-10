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
int k, n;
string a, b, s;
char to[1010];
bool us[1010];
int main() {
	int T = read();
	while(T--) {
		k = read();
		for(char c = 'a'; c <= 'a' + k - 1; ++c) to[c] = 0, us[c] = 0;
		cin >> s >> a >> b;
		n = s.size();
		bool fg = 0;
		for(int i = 0; i < n; ++i)
			if(a[i] == b[i])
				{
					if(to[s[i]]) {
						if(to[s[i]] != a[i]) {
							fg = 1;
							break;
						}
					}
					else
						to[s[i]] = a[i], us[a[i]] = 1;
				}
			else
				{
					if(to[s[i]]) {
						if(to[s[i]] < a[i] || to[a[i]] > b[i]) {
							fg = 1;
							break;
						}
					}
					else {
						for(char c = a[i]; c <= b[i]; ++c)
							if(!us[c]) {
								to[s[i]] = c;
								break;
	return 0;
}
