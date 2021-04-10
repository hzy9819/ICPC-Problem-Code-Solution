#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, m;
queue <int> ans;
bool b[N * 3];

int main() {
	Hzy("E");
	int T = read();
	while(T--) {
		n = read(), m = read();
		while(!ans.empty())
			ans.pop();
		for(int i = 1; i <= 3 * n; ++i) b[i] = 0;
		int u, v;
		for(int i = 1; i <= m; ++i) {
			u = read(), v = read();
			if(!b[u] && !b[v]) {
				b[u] = b[v] = 1;
				ans.push(i);
			}
		}
		if(ans.size() >= n) {
			puts("Matching");
			int cnt = 0;
			while(!ans.empty()) {
				cnt++;
				printf("%d ", ans.front());
				if(cnt >= n) break;
				ans.pop();
			}
			puts("");
		}
		else {
			puts("IndSet");
			int cnt = 0;
			for(int i = 1; i <= 3 * n; ++i)
				if(!b[i]) {
					cnt++;
					printf("%d ", i);
					if(cnt >= n) break;
				}
			puts("");
		}
	}
			
	return 0;
}
