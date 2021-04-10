#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 400010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int a[N], I, n, k;
int main() {
	Hzy("C");
	n = read(), I = read() * 8, k = I / n;
	if(k >= 30)
		k = n;
	else
		k = 1 << k;
	for(int i = 1; i <= n; ++i)
		a[i] = read();
	sort(a + 1, a + n + 1);
	int cnt = 0, sum = 0, Max = 0;
	a[0] = -1;
	int i;
	for(i = 1; i <= n; ++i) {
		if(a[i] != a[i - 1]) cnt++;
		if(cnt > k) break;
		sum++;
	}
	Max = sum;
	int hd = 1;
	for(; i <= n; ++i) {
		if(a[i] != a[i - 1]) {
			int tmp = hd + 1;
			while(a[tmp] == a[hd]) tmp++;
			sum -= tmp - hd;
			hd = tmp;
		}
		sum++;
		Max = max(Max, sum);
	}
	cout << n - Max << endl;
	return 0;
}
