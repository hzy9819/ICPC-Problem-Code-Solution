#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define mk(x, y) make_pair<x, y>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;
LL n, k, sum;
LL a, b, c, x0;
LL p1[N * 10], p2[N * 10];
LL tmp[N], sz;
pair<LL, int> del[N * 10];
int id1[N * 10], id2[N * 10];
bool ex[N];
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("generators");
	n = read(), k = read();
	for(int i = 1; i <= n; ++i) {
		x0 = read(), a = read(), b = read(), c = read();
		for(int j = 0; j < c; ++j) ex[j] = 0;
		sz = 0;
		while(!ex[x0]) {
			ex[x0] = 1, tmp[++sz] = x0;
			//if(p1[i] < x0) p2[i] = p1[i], id2[i] = id1[i], p1[i] = x0, id1[i] = sz;
			//else if(p2[i] < x0) p2[i] = x0, id2[i] = sz;
			x0 = (a * x0 + b) % c;
		}
		p1[i] = p2[i] = -1;
		for(int j = 1; j <= sz; ++j)
			if(p1[i] < tmp[j]) p1[i] = tmp[j], id1[i] = j - 1;
		for(int j = 1; j <= sz; ++j)
			if((p1[i] - tmp[j]) % k && tmp[j] > p2[i]) p2[i] = tmp[j], id2[i] = j - 1; 
		sum += p1[i];
		if(p2[i] != -1) del[i].first = p1[i] - p2[i];
		else del[i].first = inf;
		del[i].second = i;
	}
	sort(del + 1, del + n + 1);
	for(int i = 0; i <= n; ++i)
		if(del[i].first != inf && (sum - del[i].first) % k) {
			printf("%lld\n", sum - del[i].first);
			for(int j = 1; j <= n; ++j)
				printf("%d ", del[i].second == j ? id2[j] : id1[j]);
			return 0;
		}
	puts("-1");
	return 0;
}
