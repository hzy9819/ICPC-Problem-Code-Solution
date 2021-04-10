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
const int N = 110;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], num[N];
int ct = 0;

int main() {
	Hzy("C");
	n = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		num[a[i]]++;
	}
	for(int i = 1; i <= 100; ++i)
		if(num[i] == 1) ct++;
	if((ct & 1) == 0) {
		puts("YES");
		for(int i = 1; i <= n; ++i)
			if(num[a[i]] == 1) {
				if(ct & 1) putchar('A');
				else putchar('B');
				ct--;
			}
			else putchar('A');
		puts("");
	}
	else {
		int temp = -1;
		for(int i = 1; i <= 100; ++i)
			if(num[i] > 2) {
				temp = i;
				break;
			}
		if(temp == -1) {
			puts("NO");
			return 0;
		}
		puts("YES");
		for(int i = 1; i <= n; ++i)
			if(num[a[i]] == 1) {
				if(ct & 1) putchar('A');
				else putchar('B');
				ct--;
			}
			else if(a[i] == temp) {
				putchar('B');
				temp = -1;
			}
			else putchar('A');
	}
	return 0;
}
