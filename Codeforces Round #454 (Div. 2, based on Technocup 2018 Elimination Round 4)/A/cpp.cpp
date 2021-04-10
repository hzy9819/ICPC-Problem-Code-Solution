#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int v1, v2, v3, vm;
int main() {
	Hzy("A");
	v1 = read(), v2 = read(), v3 = read(), vm = read();
	if(v3 * 2 < vm) {
		puts("-1");
		return 0;
	}
	v3 = max(vm, v3);
	if(v2 * 2 <= v3 || v2 <= vm) {
		puts("-1");
		return 0;
	}
	v2 = max(max(2 * vm + 1, v3 + 1), v2);
	if(v1 * 2 <= v2 || v1 <= vm) {
		puts("-1");
		return 0;
	}
	v1 = max(max(2 * vm + 1, v2 + 1), v1);
	printf("%d\n%d\n%d\n", v1, v2, v3);
	return 0;
}
