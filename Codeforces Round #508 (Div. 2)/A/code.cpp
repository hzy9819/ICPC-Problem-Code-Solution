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

int n, k, sum[30];
char s[N];

int main() {
	Hzy("A");
	n = read(), k = read();
	scanf("%s", s + 1);
	for(int i = 1; i <= n; ++i)
		sum[s[i] - 'A']++;
	int Min = sum[0];
	for(int i = 1; i < k; ++i)
		Min = min(Min, sum[i]);
	cout << Min * k << endl;
	return 0;
}
