#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int ST = (1 << 20) + 10;
const int N = 25;
bool b[ST];
queue <int> Q;
int bin[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
void BFS() {
	int t, p;
	while(!Q.empty()) {
		t = Q.front(), Q.pop();
		for(int i = 0; i < m; ++i) {
			p = t ^ bin[i];
			if(!b[p]) b[p] = 1, Q.push(p);
		}
	}
	for(int i = 0; i < m; ++i) {
		if(t & bin[i]) printf("1");
		else printf("0");
	}
}
int main() {
	Hzy("D");
	n = read(), m = read();
	bin[0] = 1;
	char s[N];
	for(int i = 1; i <= m; ++i) bin[i] = (bin[i - 1] << 1);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s);
		int t = 0;
		for(int j = 0; j < m; ++j) t += bin[j] * (s[j] - '0');
		b[t] = 1, Q.push(t);
	}
	BFS();
	return 0;
}
