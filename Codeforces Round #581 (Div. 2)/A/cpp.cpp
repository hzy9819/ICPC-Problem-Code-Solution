#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
int n;
char s[N];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int ct = 0;


int main() {
	scanf("%s", s);
	n = strlen(s);
	for(int i = 0; i < n; ++i)
		ct = ct + s[i] - '0';
	n++;
	if(n & 1) ct++;
	printf("%d\n", n / 2 - (ct <= 1));
	return 0;
}
