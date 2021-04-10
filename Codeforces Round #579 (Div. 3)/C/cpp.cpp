#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 400010;

LL gcd(LL a, LL b) {
	if(a < b)
		swap(a, b);
	LL c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL a[N], n, _gcd, ans = 1;

int main() {
	n = read();
	for(int i = 0; i < n; ++i)
		a[i] = read();
	_gcd = a[0];
	for(int i = 1; i < n; ++i)
		_gcd = gcd(_gcd, a[i]);
	LL tmp = _gcd, p;
	for(LL i = 2; i <= sqrt(_gcd); ++i)
		if(tmp % i == 0) {
			p = 1;
			while(tmp % i == 0) {
				p++;
				tmp /= i;
			}
			ans = ans * p;
		}
	if(tmp != 1)
		ans = ans * 2;
	cout << ans << endl;
	return 0;
}
