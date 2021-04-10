#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 510;
const int S = 2010;
int n, k;
char s[N][S];
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("B");
	int T = read(), cnt = 1;
	while(T--) {
		n = read() ;
		for(int i = 0; i < n; ++i)
			scanf("%s", s[i]);
		int tmp = n - 1;
		while(tmp && strstr(s[tmp], s[tmp - 1]) != NULL) tmp--;
		tmp++;
		for(int i = tmp - 1; i >= 0 && tmp < n; --i)
			while(tmp < n && strstr(s[tmp], s[i]) == NULL) tmp++;
		if(tmp == 1) tmp = -1;
		printf("Case #%d: %d\n", cnt++, tmp);
	}
	return 0;
}
