#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;

struct Tp {
	string s;
	int a, b, c, d;
}a[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
int main() {
	Hzy("B");
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		cin >> a[i].s;
		scanf("%d.%d.%d.%d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
	}
	int aa, b, c, d;
	string s;
	for(int i = 1; i <= m; ++i) {
		cin >> s;
		scanf("%d.%d.%d.%d;", &aa, &b, &c, &d);
		cout << s << " ";
		printf("%d.%d.%d.%d; #", aa, b, c, d);
		for(int j = 1; j <= n; ++j)
			if(a[j].a == aa && a[j].b == b && a[j].c == c && a[j].d == d) {
				cout << a[j].s << endl;
				break;
			}
	}
	return 0;
}
