#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 150010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], ans = 0;
int main() {
	n = read();
	for(int i = 0; i < n; ++i)
		a[i] = read();
	sort(a, a + n);
	ans = 1;
	if(a[0] != 1) a[0]--;
	for(int i = 1; i < n; ++i)
		if(a[i] - 1 > a[i - 1])
			ans++, a[i]--;
		else if(a[i] - 1 == a[i - 1])
			ans++;
		else if(a[i] == a[i - 1])
			ans++, a[i]++;
		else
			a[i]++;
	cout << ans << endl;
	return 0;
}
