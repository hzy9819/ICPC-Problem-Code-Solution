#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int lm1 = (1 << 7) - 1;
int lm2 = lm1 << 7;
int suf, pre, bin[20];

int main() {
	bin[0] = 1;
	for(int i = 1; i < 20; ++i)
		bin[i] = (bin[i - 1] << 1);
	printf("? ");
	for(int i = 0; i < 100; ++i)
		printf("%d%c", i, (i == 99) ? '\n' : ' ');
	fflush(stdout);
	suf = read();
	printf("? ");
	for(int i = 1; i <= 100; ++i)
		printf("%d%c", bin[7] * i, (i == 100) ? '\n' : ' ');
	fflush(stdout);
	pre = read();
	printf("! %d\n", (pre & lm1) | (suf & lm2));
	fflush(stdout);
	return 0;
}
