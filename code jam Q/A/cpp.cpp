#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
int n, a[N];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int T;

void Rev(int * a, int i, int j) {
	while(i < j)
		swap(a[i], a[j]), i++, j--;
}

int find_min(int * a, int l, int r) {
	int pos = l;
	for(int i = l + 1; i <= r; ++i)
		if(a[i] < a[pos])
			pos = i;
	return pos;
}

int calc(int * a, int n) {
	int res = 0;
	for(int i = 1; i < n; ++i) {
		int j = find_min(a, i, n);
		res = res + j - i + 1;
		Rev(a, i, j);
	}
	return res;
}

int main() {
	T = read();
	for(int cas = 1; cas <= T; ++cas) {
		n = read();
		for(int i = 1; i <= n; ++i)
			a[i] = read();
		printf("Case #%d: %d\n", cas, calc(a, n));
	}
	return 0;
}
