#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
LL n, x = 1, y;
int main() {
	cin >> n;
	y = n;
	for(LL i = 2; i <= sqrt(n); ++i)
		if(n % i == 0) {
			x = 1;
			LL tmp = n;
			while(tmp % i == 0) {
				x *= i;
				tmp /= i;
			}
			y = tmp;
			break;
		}
	if(x > y) swap(x, y);
	if(x == 1) 
		puts("NO");
	else {
		puts("YES");
		puts("2");
		for(LL i = 1; i <= x; ++i)
			if((n - 1 - i * y) % x == 0) {
				cout << i << " " << x << endl;
				cout << (n - 1 - i * y) / x << " " << y << endl;
				break;
			}
	}
	return 0;
}
