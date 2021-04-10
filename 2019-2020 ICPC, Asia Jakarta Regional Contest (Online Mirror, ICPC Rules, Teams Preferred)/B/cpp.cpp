#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int weg = 1e9 + 7;
struct Edge {
	int to, next;
}e[N * 2];
int lst[N], d, n;
LL f[N][2];

void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
}

LL gcd(LL a, LL b) {
	if(a < b) swap(a, b);
	LL t;
	while(b) t = a % b, a = b, b = t;
	return a;
}
LL exgcd(LL a, LL b, LL z) {return a ? (exgcd(b % a, a, -z) * b + z) / a : z / b;}
LL inv(LL a, LL p) {return exgcd(a, p, 1);}

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void dfs(int t, int pre) {
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != pre)
			dfs(e[i].to, t);
	LL s1, s2, s3, s4, tmp;
	s1 = s4 = 0;
	s2 = s3 = 1;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != pre) {
			tmp = f[e[i].to][1] * inv(f[e[i].to][0], weg) % weg;
			s1 = (s1 + tmp) % weg;
			s2 = s2 * f[e[i].to][0] % weg;
			s3 = s3 * (f[e[i].to][0] + f[e[i].to][1]) % weg;
			s4 = (s4 + tmp * tmp % weg) % weg;
		}
	f[t][0] = (s1 * s1 % weg + weg - s4) % weg * s2 % weg;
	f[t][1] = s2;
	for(int i = lst[t]; i >= 0; i = e[i].next)
		if(e[i].to != pre)
			f[t][1] = (f[t][1] + f[e[i].to][1] * s3 % weg * inv(f[e[i].to][0] + f[e[i].to][1], weg) % weg) % weg;
}
		   
int main() {
	n = read();
	memset(lst, -1, sizeof lst);
	int x, y;
	for(int i = 1; i < n; ++i) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	cout << (f[1][0] + f[1][1]) % weg << endl;
	return 0;
}
