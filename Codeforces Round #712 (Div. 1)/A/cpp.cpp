#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int T, n;
string s;
int ans[N];

int main() {
	T = read();
	while(T--) {
		int s1 = 0, s2 = 0;
		n = read();
		cin >> s;
		for(int i = 0; i < n; ++i) {
			if(s[i] == '1') {
				ans[i] = 1;
				s1++, s2++;
			}
			else {
				if(s1 > s2) {
					s1--, s2++;
					ans[i] = 0;
				}
				else {
					s1++, s2--;
					ans[i] = 1;
				}
			}
			if(
	   
	return 0;
}
