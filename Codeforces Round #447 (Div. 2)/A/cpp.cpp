#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 110;
string s;
int s1[N], s2[N];
LL ans(0);
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("A");
	cin >> s;
	int n = s.size();
	for(int i = n - 1; i >= 0; --i) {
		s1[i] = s1[i + 1];
		if(s[i] == 'Q') s1[i]++;
	}
	for(int i = n - 1; i >= 0; --i) {
		s2[i] = s2[i + 1];
		if(s[i] == 'A') s2[i] += s1[i];
	}
	for(int i = 0; i < n; ++i) if(s[i] == 'Q') ans += s2[i];
	printf("%I64d\n", ans);
	return 0;
}
