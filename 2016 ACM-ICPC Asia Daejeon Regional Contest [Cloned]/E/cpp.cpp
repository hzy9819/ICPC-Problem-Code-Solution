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
const int N = 2010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
bool IsNum(char c) { return c >= '0' && c <= '9'; }
struct Node {
	int l, r;
	string s;
}a[N];
int n;
string s;
int cnt, st1[N], st2[N], sz1, sz2;
int Pri[256];
bool fg;
void Merge() {
	char c = a[st2[sz2]].s[0];
	if(c == ')') {
		sz2--;
		while(sz2 && a[st2[sz2]].s[0] != '(') {
			Merge();
			if(fg) return ;
		}
		if(fg || a[st2[sz2]].s[0] != '(') {
			fg = 1;
			return ;
		}
		sz2--;
	}
	else if(c == '(') return ;
	else {
		if(sz1 < 2) {
			fg = 1;
			return ;
		}
		a[st2[sz2]].l = st1[sz1 - 1], a[st1[sz1]].r = st1[sz1];
		st1[--sz1] = st2[sz2--];
	}
}
int main() {
	Hzy("E");
	Pri['('] = 0;
	Pri['+'] = Pri['-'] = 1;
	Pri['*'] = Pri['/'] = 2;
	Pri[')'] = 3;
	while(getline(cin, s)) {
		n = s.size();
		cnt = sz1 = sz2 = 0;
		fg = 0;
		string tmp;
		for(int i = 0; i < n; ++i) {
			if(s[i] == ' ') continue;
			if(IsNum(s[i])) {
				//tmp = "";
				tmp = s[i];
				while(i + 1 < n && IsNum(s[i + 1])) {
					if(tmp[0] == '0') tmp[0] = s[i + 1];
					else tmp += s[i + 1];
					i++;
				}
				i--;
				a[++cnt].s = tmp, a[cnt].l = a[cnt].r = 0;
				st1[++sz1] = cnt;
			}
			else {
				a[++cnt].s = s[i], a[cnt].l = a[cnt].r = 0;
				while(sz2 && Pri[a[st2[sz2]].s[0]] >= Pri[s[i]]) {
					Merge();
					if(fg) break;
				}
				st2[++sz2] = cnt;
			}
			if(fg) {
				puts("ERROR");
				break;
			}
		}
		while(sz2) {
			if(a[st2[sz2]].s[0] == '(') fg = 1;
			Merge();
			if(fg) {
				puts("ERROR");
				break;
			}
		}
		if(fg) continue;
		puts("OK");
	}
	return 0;
}
