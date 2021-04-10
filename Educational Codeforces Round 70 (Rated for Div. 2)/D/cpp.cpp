#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int LEN = 20000;
const int N = 100010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
char ans[N];

vector <LL> v;

void Solve(int n) {
	v.clear();
	LL l = 2;
	while(l * (l - 1) / 2 < n) l++;
	LL now = l;
	while(n) {
		while(now * (now - 1) / 2 > n) now--;
		while(now * (now - 1) / 2 <= n) {
			n -= now * (now - 1) / 2;
			v.push_back(now);
		}
	}
	size_t p = 0;
	while(l) {
		while(p < v.size() && v[p] == l)
			printf("1"), p++;
		printf("3");
		l--;
	}
	puts("7");	
}
	
int main() {
	int T = read();
	while(T--)
		Solve(read());
	return 0;
}
