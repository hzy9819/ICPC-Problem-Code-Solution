#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
int n, pos = -1, sum;
string s;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("B");
	cin >> s;
	n = s.size();
	for(int i = 0; i < n; ++i)
		if(s[i] == '1') sum++;
		else if(s[i] == '2' && pos == -1) pos = i;
	for(int i = 0; i < n; ++i) {
		if(i == pos)
			for(int j = 1; j <= sum; ++j)
				putchar('1');
		if(s[i] != '1')
			putchar(s[i]);
	}
	if(pos == -1)
		for(int i = 1; i <= sum; ++i)
			putchar('1');
	return 0;
}
