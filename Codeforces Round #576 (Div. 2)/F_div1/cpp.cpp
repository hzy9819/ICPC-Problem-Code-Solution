#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;

int n, a[N], id[N], ans[N];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int gcd(int a, int b) {
	if(a < b) swap(a, b);
	int c;
	while(b)
		c = a % b, a = b, b =c ;
	return a;
}

int main() {
	n = read();
	for(int i = 0; i < n; ++i)
		a[i] = read(), id[i] = i;
	clock_t begin = clock();
	while(clock() - begin < 0.4 * CLOCKS_PER_SEC) {
		random_shuffle(id, id + n);
		int X = 0, Y = 0;
		for(int i = 0; i < n; ++i) {
			int tmp = gcd(X, a[id[i]]);
			if(tmp == X)
				Y = gcd(Y, a[id[i]]), ans[id[i]] = 2;
			else
				X = tmp, ans[id[i]] = 1;
		}
		if(X == 1 && Y == 1) {
			puts("YES");
			for(int i = 0; i < n; ++i)
				printf("%d ", ans[i]);
			return 0;
		}
	}
	puts("NO");
	return 0;
}
