#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int c[7][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 3, 5, 7, 9, 11, 24, 22},
	{2, 4, 6, 8, 10, 12, 23, 21},
	{13, 14, 6, 8, 10, 12, 23, 21},
	{15, 16, 7, 8, 19, 20, 23, 24},
	{1, 2, 22, 24, 18, 20, 15, 13},
	{3, 4, 17, 19, 10, 9, 16, 14}
}; 

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int a[30], b[30];
bool check(int *b) {
	for(int i = 1; i <= 6; ++i) {
		int t = 4 * (i - 1) + 1;
		if(b[t + 1] != b[t] || b[t + 2] != b[t] || b[t + 3] != b[t]) return 0;
	}
	return 1;
}
void Change1(int t) {
	for(int i = 1; i <= 24; ++i) b[i] = a[i];
	int p;
	for(int i = 2; i < 8; ++i) {
		p = i - 2;
		b[c[t][i]] = a[c[t][p]];
	}
	b[c[t][0]] = a[c[t][6]];
	b[c[t][1]] = a[c[t][7]];
}
void Change2(int t) {
	for(int i = 1; i <= 24; ++i) b[i] = a[i];
	int p;
	for(int i = 2; i < 8; ++i) {
		p = i - 2;
		b[c[t][p]] = a[c[t][i]];
	}
	b[c[t][6]] = a[c[t][0]];
	b[c[t][7]] = a[c[t][1]];
}
bool fg;
int main() {
	Hzy("B");
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d %d\n", a + 7, a + 5, a + 8, a + 6);
		scanf("%d %d %d %d\n", a + 19, a + 17, a + 20, a + 18);
		scanf("%d %d %d %d\n", a + 23, a + 21, a + 24, a + 22);
		scanf("%d %d %d %d\n", a + 15, a + 13, a + 16, a + 14);
		scanf("%d %d %d %d\n", a + 11, a + 9, a + 12, a + 10);
		scanf("%d %d %d %d\n", a + 3, a + 1, a + 4, a + 2);
		/*a[7] = read(), a[5] = read(), a[8] = read(), a[6] = read();
		a[19] = read(), a[17] = read(), a[20] = read(), a[18] = read();
		a[23] = read(), a[21] = read(), a[24] = read(), a[22] = read();
		a[15] = read(), a[13] = read(), a[16] = read(), a[14] = read();
		a[11] = read(), a[9] = read(), a[12] = read(), a[10] = read();
		a[3] = read(), a[1] = read(), a[4] = read(), a[2] = read();*/
		fg = 0;
		if(check(a)) fg = 1;
		for(int i = 1; i <= 6; ++i) {
			Change1(i);
			if(check(b)) {
				//puts("YES");
				fg = 1;
				break;
			}
			Change2(i);
			if(check(b)) {
				//puts("YES");
				fg = 1;
				break;
			}
		}
		if(fg) puts("YES");
		else puts("NO");
	}
	return 0;
}
