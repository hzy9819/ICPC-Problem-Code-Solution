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
int n, a[N];

int main() {
	Hzy("B");
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	sort(a + 1, a + n + 1);
	LL sum = 0;
	for(int i = 1; i < n; ++i)
		sum += a[i];
	if(sum < a[n]) {
		puts("NO");
		return 0;
	}
	sum += a[n];
	if(sum & 1) {
		puts("NO");
		return 0;
	}
	puts("YES");
	
	return 0;
}
