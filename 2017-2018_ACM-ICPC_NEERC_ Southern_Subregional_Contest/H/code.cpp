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
const int N = 400010;
const int seed = 137;
const int weg = 998244353;
char s[N], ans[N];
int n;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int sum[200], num, st[N];
bool check(int t) { //t means num
	if(n % t) return 0;
	if(!t) return 0;
	if(num && ((n / t) % 2 == 0)) return 0;
	int tmp = n / t;
	int t1, t2, tp;
	t1 = 0, t2 = 1;
	tp = tmp / 2;
	printf("%d\n", t);
	for(int i = 1; i <= t; ++i) {
		//while(sum[st[t2]] == 0 && t2 <= num) t2++;
		if(num) {
			if(t2 <= num) {
				//while(!sum[st[t2]] && t2 <= num) t2++;
				ans[tp + 1] = st[t2], t2++;
			}
			else {
				while(!sum[t1]) t1++;
				sum[t1] -= 2, ans[tp + 1] = t1, st[++num] = t1;
			}
		}
		for(int j = 1; j <= tp; ++j) {
			while(sum[t1] < 2) t1++;
			ans[j] = ans[tmp - j + 1] = t1, sum[t1] -= 2;
		}
		for(int j = 1; j <= tmp; ++j) putchar(ans[j]);
		printf(" ");
	}
	return 1;
}
int main() {
	//Hzy("H");
	scanf("%d\n", &n);
	for(int i = 1; i <= n; ++i) s[i] = getchar(), sum[s[i]]++;
	for(int i = '0'; i <= 'z'; ++i) if(sum[i] & 1) st[++num] = i, sum[i]--;
	if(!num) check(1);
	else for(int i = num; i <= n; i += 2) if(check(i)) break;
	return 0;
}
