#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, m, k;
int h[N];

int main() {
	int T = read();
	while(T--) {
		n = read(), m = read(), k = read();
		for(int i = 1; i <= n; ++i)
			h[i] = read();
		bool fg = 0;
		for(int i = 1; i < n; ++i)
			if(h[i] >= max(0, h[i + 1] - k))  
				m += h[i] - max(0, h[i + 1] - k);		
			else {
				m -= h[i + 1] - k - h[i];
				if(m < 0) {
					fg = 1;
					break;
				}
			}
		fg ? puts("NO") : puts("YES");
	}
				
			
	return 0;
}
