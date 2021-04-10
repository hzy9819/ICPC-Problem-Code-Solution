#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 1010;
const LL seed = 1031;
const int weg = 998244353;
LL bin[N];
int Hs(int *a, int n) {
	LL res(0);
	for(int i = 1; i <= n; ++i) res = (res + bin[a[i]]) % weg;
	return res;
}
struct Son {
	int l, r;
};
int n, sz, a[N * N], Po, d, fg;
bool b[N][N];
void add(int x, int y) {
	d++;
	b[x][y] = 1;
}
//vector <int> v[N];
vector <Son> v[N];
vector <int> t[N];
map <int, bool> M[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Impos() {
	puts("-1");
	exit(0);
}
int main() {
	//Hzy("L");
	n = read(), Po = 1;
	bin[1] = 1;
	for(int i = 2; i <= n; ++i) bin[i] = (bin[i - 1] << 1) % weg;
	fg = ((bin[n] << 1) - 1) % weg;
	for(int i = 1; i <= n; ++i) {
		int x, now, tmp; char c;
		do {
			scanf("%d", &x), now = Po;
			for(int j = 1; j <= x; ++j)
				scanf("%c%d", &c, &a[Po++]);
			//a[Po++] = i;
			//sort(a + now, a + Po);
			tmp = Hs(a + now - 1, x);
			t[i].push_back(tmp);
			M[i][tmp] = 1;
			v[i].push_back((Son){now, Po - 1});
			//v[i].push_back(Hs(a[now], x + 1));
			c = getchar();
		}while(c == '-');
	}
	for(int i = 1; i <= n; ++i) 
		for(int j = 0; j < v[i].size(); ++j) {
			int tmp = (fg - t[i][j] + weg) % weg, k;
			for(k = v[i][j].l; k <= v[i][j].r; ++k) if(a[k] != i) {
					if(b[i][a[k]] || b[a[k]][i]) break;
					if(M[a[k]][tmp]) {add(i, a[k]); break;}
				}
			if(k > v[i][j].r) Impos();
		}
	if(d < n - 1) Impos();
	printf("%d\n", n - 1);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) if(b[i][j]) printf("%d %d\n", i, j);
	return 0;
}
