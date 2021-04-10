#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
int n;
char c[N];
int f[N], s[N], st[N], sz, fr, ed;
int ans1, ans2;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int calc(int l, int r) {
	if(l > r) return 0;
	else return s[r] - s[l - 1];
}
bool check(int k) {
	for(int i = 1; i <= sz; ++i) {
		if(calc(f[i - 1] + 1, st[i] - k - 1)) return false;
		else if(calc(f[i - 1] + 1, st[i] - 1) == 0) f[i] = st[i] + k;
		else if(i > 1 && calc(f[i - 2] + 1, st[i] - k - 1) == 0) f[i] = max(st[i], st[i - 1] + k);
		else f[i] = st[i];
	}
	if(calc(f[sz] + 1, n)) return false;
	return true;
}
int main() {
	Hzy("D");
	n = read();
	scanf("%s", c + 1);
	for(int i = 1; i <= n; ++i) {
		s[i] = s[i - 1];
		if(c[i] == 'P') st[++sz] = i;
		if(c[i] == '*') {
			s[i]++;
			if(!fr) fr = i;
			ed = i;
		}
	}
	if(sz == 1) {
		int n1 = s[st[1]], t1 = max(0, st[1] - fr);
		int n2 = s[n] - n1, t2 = max(0, ed - st[1]);
		if(n1 > n2) ans1 = n1, ans2 = t1;
		else if(n1 < n2) ans1 = n2, ans2 = t2;
		else ans1 = n1, ans2 = min(t1, t2);
	}
	else {
		int l, r, mid;
		for(l = 0, r = n, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
			if(check(mid)) ans2 = mid, r = mid - 1;
			else l = mid + 1;
		}
		ans1 = s[n];
	}
	printf("%d %d\n", ans1, ans2);
	return 0;
}
		
	
