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

int n, b[N], a[N];
bool fg = 0, vis[N];
string s;

void dfs(int t) {
	if(t < 0) {
		for(int i = n / 2; i >= 0; --i)
			printf("%d", a[i]);
		puts("");
		fg = 1;
		return ;
	}
	int t1 = -1, t2 = -1;
	for(int i = min(n / 2, t); i >= 0; --i) {
		int j = t - i;
		if(j < 0 || j > n / 2)
			break;
		if(!vis[i] || !vis[j]) 
			t1 = i, t2 = j;
		else 
			b[t] = (b[t] + 10 - a[i] * a[j] % 10) % 10;
	}
	if(t1 == -1 && b[t] != 0) {
		for(int i = min(n / 2, t); i >= 0; --i) {
			int j = t - i;
			if(j < 0 || j > n / 2)
				break;
			b[t] = (b[t] + a[i] * a[j] % 10) % 10;
		}
		return ;
	}
	if(t1 == -1)
		dfs(t - 1);
	else {
		if(t1 == t2) {
			for(int i = 0; i < 10; ++i)
				if(i * i % 10 == b[t]) {
					a[t1] = i, vis[t1] = 1;
					dfs(t - 1);
					if(fg)
						return ;
					vis[t1] = 0;
				}
		} else {
			if(t1 > t2)
				swap(t1, t2);
			for(int i = 0; i < 10; ++i)
				if(2 * a[t2] * i % 10 == b[t]) {
					a[t1] = i, vis[t1] = 1;
					dfs(t - 1);
					if(fg)
						return ;
					vis[t1] = 0;
				}
		}
	}
	for(int i = min(n / 2, t); i >= 0; --i) {
			int j = t - i;
			if(j < 0 || j > n / 2)
				break;
			if(!vis[i] || !vis[j])
				continue;
			b[t] = (b[t] + a[i] * a[j] % 10) % 10;
	}
}
	   			

int main() {
	cin >> s;
	n = s.size();
	if((n & 1) == 0)
		return puts("-1"), 0;
		
	for(int i = 0; i < n; ++i)
		b[n - i - 1] = s[i] - '0';

	dfs(n - 1);
	if(!fg)
		puts("-1");
	
	return 0;
}
