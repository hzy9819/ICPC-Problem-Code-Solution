#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
int n, a[N], m, k, x;
vector <int> v[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	//Hzy("B");
	n = read(), k = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) {
		x = a[i] % m;
		v[x].push_back(a[i]);
		if(v[x].size() >= k) {
			puts("Yes");
			for(int j = 0; j < v[x].size(); ++j)
				printf("%d ", v[x][j]);
			return 0;
		}
	}
	puts("No");
	return 0;
}
