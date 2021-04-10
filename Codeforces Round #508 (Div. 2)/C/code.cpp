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
const int N = 100010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], b[N], p1, p2;
LL A, B;
int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) b[i] = read();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	p1 = p2 = n;
	for(int i = 1; i <= n; ++i) {
		if(a[p1] > b[p2]) A += a[p1--];
		else p2--;

		if(b[p2] > a[p1]) B += b[p2--];
		else p1--;
	}
	cout << A - B << endl;
	return 0;
}
