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
const int N = 500010;
int st[15]; // -1 : none, 0 : to 0, 1 : to 1, 2 : ^, 3 : & 1   | all to 1, ^ -1 -> 2, 0 -> 1, 1 -> 0, 2 -> -1, 3 -> 2, & -1 -> 3, 0 -> 0, 1 -> 1, 2 -> 2, 3 -> 3
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Or(int t) {
	st[t] = 1;
}
void Nor(int t) {
	st[t] = 0;
}
void Xor(int t) {
	if(st[t] == -1) st[t] = 2;
	else if(st[t] == 0) st[t] = 1;
	else if(st[t] == 1) st[t] = 0;
	else if(st[t] == 2) st[t] = 3;
	else if(st[t] == 3) st[t] = 2;
}
void And(int t) {
	if(st[t] == -1) st[t] = 3;
}
void Out() {
	puts("3");
	int tmp;
	tmp = 0;
	for(int i = 0; i < 10; ++i) if(st[i] != 0) tmp |= (1 << i);
	printf("& %d\n", tmp);
	tmp = 0;
	for(int i = 0; i < 10; ++i) if(st[i] == 1) tmp |= (1 << i);
	printf("| %d\n", tmp);
	tmp = 0;
	for(int i = 0; i < 10; ++i) if(st[i] == 2) tmp |= (1 << i);
	printf("^ %d\n", tmp);
}
int n;
int main() {
	Hzy("C");
	n = read();
	for(int i = 0; i < 10; ++i) st[i] = 3;
	char c;
	int x;
	for(int i = 1; i <= n; ++i) {
		c = getchar();
		while(c != '|' && c != '&' && c != '^') c = getchar();
		x = read();
		for(int j = 0; j < 10; ++j) {
			if(x & 1) {
				if(c == '|') Or(j);
				else if(c == '&') And(j);
				else if(c == '^') Xor(j);
			}
			else {
				if(c == '&') Nor(j);
			}
			x >>= 1;
		}
	}
	Out();
	return 0;
}
