#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
LL n, m, k;
LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL gcd(LL a, LL b) {
	if(a < b) swap(a, b);
	LL c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

int main() {
	Hzy("A");
	n = read(), m = read(), k = read();
	if((n * m * 2) % k)
		puts("NO");
	else {
		//k = n * m * 2 / k;
		//k *= 2;
		LL a = gcd(n, k);
		k /= a;
		LL b = gcd(m, k);
		k /= b;
		a = n / a;
		b = m / b;
		if(k == 1) {
			if(a * 2 <= n) a *= 2;
			else b *= 2;
		}
		else if(k != 2) return puts("NO"), 0;
		puts("YES");
		puts("0 0");
		cout << a << " " << 0 << endl;
		cout << 0 << " " << b << endl;
	}
	return 0;
}
