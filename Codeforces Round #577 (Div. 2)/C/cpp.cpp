#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL n, k, a[N], ans;
int main() {
	Hzy("C");
	n = read(), k = read();
	for(int i = 0; i < n; ++i)
		a[i] = read();
	sort(a, a + n);
	LL cnt = 1, del;
	ans = a[n / 2];
	for(int i = n / 2; i < n - 1; ++i) {
		del = a[i + 1] - a[i];
		if(cnt * del <= k) {
			k -= cnt * del;
			ans = a[i + 1];
			cnt++;
		}
		else {
			ans += k / cnt;
			k = 0;
			break;
		}
	}
	if(k)
		ans += k / cnt;
	cout << ans << endl;
	return 0;
}
