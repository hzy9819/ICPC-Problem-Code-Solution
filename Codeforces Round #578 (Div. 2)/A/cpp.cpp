#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

bool b[20];
int n;
char s[N];

int main() {
	n = read();
	scanf("%s", s);
	n = strlen(s);
	for(int i = 0; i < n; ++i)
		if(s[i] == 'L') {
			for(int j = 0; j < 10; ++j)
				if(!b[j]) {
					b[j] = 1;
					break;
				}
		}
		else if(s[i] == 'R') {
			for(int j = 9; j >= 0; --j)
				if(!b[j]) {
					b[j] = 1;
					break;
				}
		}
		else
			b[s[i] - '0'] = 0;

	for(int i = 0; i < 10; ++i)
		printf("%c", b[i] ? '1' : '0');
				
	return 0;
}
