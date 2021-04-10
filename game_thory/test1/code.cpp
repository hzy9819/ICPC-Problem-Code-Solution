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
const int N = 1000010;
int mex[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n = 10000;
int sz, p[N], sg[N];
bool b[N];
void Prime() {
	for(int i = 2; i <= 100000; ++i) {
		if(!b[i]) p[++sz] = i;
		for(int j = 1; j <= sz && i * p[j] <= 100000; ++j) {
			b[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
int Mex(int t) {
	int ans = 0;
	mex[sg[1]] = t;
	for(int i = 1; i <= sz && p[i] <= t; ++i) if(t % p[i] == 0) {
			if(mex[sg[t - p[i]]] != t) mex[sg[t - p[i]]] = t;
			while(mex[ans] == t) ans++;
		}
	return ans;
}
int main() {
	freopen("data.out", "w", stdout);
	Prime() ;
	for(int i = 1; i <= n; ++i)
		sg[i] = Mex(i);
	for(int i = 1; i <= n; ++i)
		printf("sg(%d) = %d\n", i, sg[i]);
	return 0;
}
