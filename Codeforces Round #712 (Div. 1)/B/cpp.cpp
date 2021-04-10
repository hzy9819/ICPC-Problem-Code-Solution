#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
int a[N][N];

pair<int, int> find_pos(int typ) {
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(((i + j) & 1) == typ && a[i][j] == 0)
				return mk(i, j);
	return mk(-1, -1);
}

int main() {
	cin >> n;
	int T = n * n;
	while(T--) {
		int typ;
		cin >> typ;
		if(typ == 1) {
			pair<int, int> p = find_pos(0);
			if(p == mk(-1, -1)) {
				p = find_pos(1);
				printf("3 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 3;
			}
			else {
				printf("2 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 2;
			}
		}
		if(typ == 2) {
			pair<int, int> p = find_pos(1);
			if(p == mk(-1, -1)) {
				p = find_pos(0);
				printf("3 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 3;
			}
			else {
				printf("1 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 1;
			}
		}
		if(typ == 3) {
			pair<int, int> p = find_pos(1);
			if(p == mk(-1, -1)) {
				p = find_pos(0);
				printf("2 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 2;
			}
			else {
				printf("1 %d %d\n", p.l, p.r);
				a[p.l][p.r] = 1;
			}
		}
		fflush(stdout);
	}
	return 0;
}
