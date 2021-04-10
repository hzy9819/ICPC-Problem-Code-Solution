#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int K = 20;
const LL LIM = 1e15;
const int N = 100010;
LL a[N], r[N], n, f[N];
LL exgcd(LL a, LL b, LL & x, LL & y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	LL ret = exgcd(b, a % b, y, x);
	y -= (a / b) * x;
	return ret;
}
LL excrt() {
	LL M = a[1], R = r[1], x, y, d, tmpa, tmpb, c, tmp;
	for(int i = 2; i <= n; ++i) {
		tmpa = M, tmpb = a[i];
		d = exgcd(tmpa, tmpb, x, y);
		c = r[i] - R;
		if(c % d)
			return -1;
		tmp = tmpb / d;
		x = (x * (c / d) % tmp + tmp) % tmp;
		R = M * x + R;
		M = M / d * a[i];
	}
	return R;
}
LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = read(), r[i] = read();
	n = excrt();
	if(n == -1) {
		printf("Tankernb!\n");
		return 0;
	}
	if(!n || n == 1) {
		printf("Lbnb!\n");
		return 0;
	}
	f[0] = 1, f[1] = 1;
	for(int i = 2; ; ++i) {
		f[i] = f[i - 1] + f[i - 2];
		if(n == f[i]) {
			printf("Lbnb!\n");
			return 0;
		}
		if(n < f[i])
			break;
	}
	printf("Zgxnb!");
	return 0;
}
