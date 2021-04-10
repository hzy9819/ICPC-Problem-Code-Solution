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
const int N = 300010;
LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int calc(LL t) {
	int res = 0;
	while(t)
		res++, t &= (t - 1);
	return res;
}

int a[N], n;
LL res, s[2];
int q[N], l, r;

int main() {
	Hzy("B");
	n = read();
	for(int i = 1; i <= n; ++i)
		a[i] = calc(read());
	for(int i = 1; i <= n; ++i) {
		if(a[i] & 1) res += s[1], swap(s[0], s[1]), s[1]++;
		else res += s[0], s[0]++;
	}
	for(int i = 1; i < n; ++i)
		if(!((a[i] + a[i + 1]) & 1) && a[i] != a[i + 1]) res--;
	for(int i = 3; i <= min(n, 65); ++i) {
		l = 1, r = 0;
		int sum = 0;
		for(int j = 1; j <= i; ++j) {
			q[++r] = j;
			sum += a[j];
			while(r > l && a[q[r]] >= a[q[r - 1]]) q[r - 1] = q[r--];
		}
		if(!(sum & 1) && a[q[l]] > sum - a[q[l]]) res--;
		for(int j = 2; j + i - 1 <= n; ++j) {
			if(j > q[l]) l++;
			q[++r] = j + i - 1;
			sum += a[j + i - 1] - a[j - 1];
			while(r > l && a[q[r]] >= a[q[r - 1]]) q[r - 1] = q[r--];
			if(!(sum & 1) && a[q[l]] > sum - a[q[l]]) res--;
		}
	}
	cout << res << endl;
	return 0;
}
