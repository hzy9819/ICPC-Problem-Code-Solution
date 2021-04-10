#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#define LL long long
#define db double
#define IsLegal(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 200010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
struct Edge {
	int to, next;
}e[N];
int lst[N], d, dg[N];
void add(int x, int y) {
	e[d].to = y, e[d].next = lst[x], lst[x] = d++;
	dg[x]++, dg[y]--;
}
int n;
int num[255];
char s[10];
stack <char> sta;
int calc(char a, char b) {
	return a * ('z' + 1) + b;
}
int S, T;
void dfs(int t) {
	int tmp;
	for(int & i = lst[t]; i >= 0;) {
		tmp = e[i].to;
		i = e[i].next;
		dfs(tmp);
		sta.push((char) (tmp % ('z' + 1)));
	}
}
int main() {
	Hzy("D");
	n = read() ;
	memset(lst, -1, sizeof lst);
	int x, y;
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s);
		if(!IsLegal(s[0]) || !IsLegal(s[1]) || !IsLegal(s[2]))
			return puts("NO"), 0;		
		x = calc(s[0], s[1]);
		y = calc(s[1], s[2]);
		add(x, y);
	}
	S = T = 0;
	for(int i = 0; i <= ('z' + 1) * ('z' + 1) ; ++i)
		if(dg[i] != 0) {
			if(abs(dg[i]) != 1) return puts("NO"), 0;
			if(dg[i] == 1) {
				if(S) return puts("NO"), 0;
				S = i;
			}
			else {
				if(T) return puts("NO"), 0;
				T = i;
			}
		}
	if((S && !T) || (!S && T)) return puts("NO"), 0;
	if(!S) {
		for(int i = 0; i <= ('z' + 1) * ('z' + 1); ++i)
			if(lst[i] != -1) {
				S = i;
				break;
			}
	}
	dfs(S);
	if(sta.size() != n) return puts("NO"), 0;
	sta.push((char) (S % ('z' + 1)));
	sta.push((char) (S / ('z' + 1)));
	puts("YES");
	while(!sta.empty())
		putchar(sta.top()), sta.pop();
	return 0;
}
