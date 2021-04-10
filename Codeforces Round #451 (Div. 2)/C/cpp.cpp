#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 25;
const int M = 15;
int n, sz;
int cmp(char * s1, char * s2) {
	int n = strlen(s1), m = strlen(s2);
	if(n > m) {
		//swap(n, m), swap(s1, s2), f = 1;
		for(int i = 1; i <= m; ++i)
			if(s1[n - i] != s2[m - i]) return 0;
		return -1;
	}
	for(int i = 1; i <= n; ++i)
		if(s1[n - i] != s2[m - i]) return 0;
	return 1;
}
struct per {
	int sz;
	char nm[M], s[210][M];
}a[N];
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
char s[M];
int main() {
	Hzy("C");
	scanf("%d", &n);
	int x, p, tp;
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s), scanf("%d", &x);
		p = 0;
		for(int j = 1; j <= sz; ++j)
			if(strcmp(s, a[j].nm) == 0) p = j;
		if(!p) sz++, p = sz, strcpy(a[p].nm, s);
		for(int j = 1; j <= x; ++j) {
			scanf("%s", s); tp = 0;
			for(int k = 1; k <= a[p].sz; ++k) {
				tp = cmp(s, a[p].s[k]);
				if(tp == 0) continue;
				if(tp == 1) break;
				if(tp == -1) strcpy(a[p].s[k], s);
				break;
			}
			if(tp == 0) strcpy(a[p].s[++a[p].sz], s);
		}
	}
	printf("%d\n", sz);
	for(int i = 1; i <= sz; ++i) {
		printf("%s %d ", a[i].nm, a[i].sz);
		//cout << a[i].nm << " " << a[i].sz << " ";
		for(int j = 1; j <= a[i].sz; ++j)
			printf("%s ", a[i].s[j]);
		//cout << a[i].s[j] << " ";
		puts("");
	}
	return 0;
}
