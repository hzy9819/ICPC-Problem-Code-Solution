#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 2010;
LL gcd(LL a, LL b) {
	if(a < b) swap(a, b);
	LL c;
	while(b) 
		c = a % b, a = b, b = c;
	return a;
}
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
LL a[N], sum;
int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		if(a[i] == 1) sum++;
	}
	if(sum) {
		printf("%I64d", n - sum);
		return 0;
	}
	LL Min = INF, tmp;
	for(int i = 1; i <= n; ++i) {
		tmp = a[i];
		for(int j = i + 1; j <= n && j - i < Min; ++j) {
			tmp = gcd(tmp, a[j]);
			if(tmp == 1) Min = j - i;
		}
	}
	if(Min == INF) puts("-1");
	else printf("%I64d", n + Min - 1);
	return 0;
}
