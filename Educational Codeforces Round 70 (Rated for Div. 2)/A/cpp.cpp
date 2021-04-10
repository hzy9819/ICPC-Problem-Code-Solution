#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

char s1[N], s2[N];
int n1, n2;

int main() {
	int T = read();
	while(T--) {
		scanf("%s", s1);
		scanf("%s", s2);
		n1 = strlen(s1), n2 = strlen(s2);
		int p1 = n1 - 1, p2 = n2 - 1, k = 0;
		while(s2[p2] != '1')
			p2--, p1--;
		while(s1[p1] != '1')
			p1--, k++;
		printf("%d\n", k);
	}
	return 0;
}
