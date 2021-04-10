#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

LL a, b, c;
string s, f[100];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	cin >> s;
	for(int i = 2; i < s.size(); ++i) {
		int temp = (s[i - 1] - 'A') + (s[i - 2] - 'A');
		temp = temp % 26;
		if(temp != (s[i] - 'A')) {
			puts("NO");
			return 0;
		}
	}
	puts("YES");
		
	return 0;
}
