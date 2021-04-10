#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, k;
int base[200], tp(0), now(0);
int main() {
	Hzy("B");
	int * num = base + 100;
	n = read(), k = read();
	while(n) {
		if(n & 1) num[tp]++, now++;
		tp++, n >>= 1;
	}
	if(now > k) {
		puts("No");
		return 0;
	}
	while(now < k) {
		if(num[tp] <= k - now) {
			num[tp - 1] += num[tp] * 2;
			now += num[tp];
			num[tp] = 0;
			tp--;
		}
		else
			break;
	}
	int low;
	for(int i = -20; i <= tp; ++i)
		if(num[i]) {
			low = i;
			break;
		}
	num[low]--;
	puts("Yes");
	for(int j = 64; j >= -20; --j) 
		for(int i = 1; i <= num[j]; ++i)
			printf("%d ", j);
	if(now == k) printf("%d ", low);
	else {
		for(int i = 1; i < k - now; ++i) printf("%d ", low - i);
		printf("%lld %lld", low - (k - now), low - (k - now));
	}
	return 0;
}
