#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;

char s[N], t[N];
int n, m, pre[N], nxt[N], ans;


int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	scanf("%s", s);
	scanf("%s", t);
	n = strlen(s), m = strlen(t);
	int p = 0;
	for(int i = 0; i < n && p < m; ++i)
		if(s[i] == t[p])
			pre[p++] = i;
	ans = max(pre[0], n - pre[m - 1] - 1);
	p = m - 1;
	for(int i = n - 1; i >= 0 && p >= 0; --i)
		if(s[i] == t[p])
			nxt[p--] = i;
	ans = max(ans, max(nxt[0], n - nxt[m - 1] - 1));
	for(int i = 0; i < m - 1; ++i)
		ans = max(ans, nxt[i + 1] - pre[i] - 1);
	cout << ans << endl;
	return 0;
}
