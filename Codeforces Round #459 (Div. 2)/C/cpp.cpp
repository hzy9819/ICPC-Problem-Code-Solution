#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 5010;
char s[N];
struct Stu {
	int num, st;
};
int n, ans;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("C");
	Stu now;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i = 1; i <= n; ++i) {
		now.num = now.st = 0;
		for(int j = i; j <= n; ++j) {
			if(s[j] == ')') {
				now.st--;
				if(now.st < now.num) now.st++, now.num--;
			}
			else if(s[j] == '(') now.st++;
			else if(now.st <= now.num) now.st++;
			else now.num++;
			if(now.num >= abs(now.st) && ((now.num - abs(now.st)) % 2 == 0)) ans++;
			else if(now.st + now.num < 0) break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
