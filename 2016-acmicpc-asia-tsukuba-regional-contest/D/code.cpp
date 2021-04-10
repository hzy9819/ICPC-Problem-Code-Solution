#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#define LL long long
#define db double
#define UN unsigned
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 4010;
const LL seed = 4013;
const LL weg = 1000010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL calc(int * t) {
	LL sum = 0;
	for(int i = 0; i < 26; ++i)
		sum = sum * seed + t[i];
	return sum;
}
char a[N], b[N];
int s1[N][30], s2[N][30], ans;
set <LL> s;
int main() {
	Hzy("D");
	scanf("%s", a + 1);
	scanf("%s", b + 1);
	int n1 = strlen(a + 1), n2 = (strlen(b + 1));
	if(n1 > n2) swap(a, b), swap(n1, n2);
	int t1[30], t2[30];
	for(int i = 1; i <= n1; ++i)
		for(int j = 0; j < 26; ++j)
			s1[i][j] = s1[i - 1][j] + ((a[i] - 'a') == j);
	for(int i = 1; i <= n2; ++i)
		for(int j = 0; j < 26; ++j)
			s2[i][j] = s2[i - 1][j] + ((b[i] - 'a') == j);
	for(ans = n1; ans > 0; --ans) {
		s.clear();
		bool fg = 0;
		for(int i = 1; i + ans - 1 <= n1; ++i) {
			int j = i + ans - 1;
			for(int k = 0; k < 26; ++k)
				t1[k] = s1[j][k] - s1[i - 1][k];
			s.insert(calc(t1));
		}
		for(int i = 1; i + ans -1 <= n2; ++i) {
			int j = i + ans - 1;
			for(int k = 0; k < 26; ++k)
				t2[k] = s2[j][k] - s2[i - 1][k];
			if(s.find(calc(t2)) != s.end()) {
				fg = 1;
				break;
			}
		}
		if(fg) break;
	}
	printf("%d\n", ans);		
	return 0;
}
