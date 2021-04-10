#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	int n = read();
	int l = 1, r = 2;
	if(n <= 2)
		puts("1");
	else {
		for(int i = 1; r < n; ++i)
			if(i & 1)
				l = r * 2, r = l + 1;
			else
				l = r * 2 - 1, r = l + 1;
		if(n == l || n == r)
			puts("1");
		else
			puts("0");
	}
	return 0;
}
