#include <bits/stdc++.h>
#define LL long long
#define db double
#define mk(a, b) make_pair(a, b)
#define l first
#define r second
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, w;
int l, r;
pair<int, int> qu[N];
vector <int> v[N];
LL s[N];

int main() {
	n = read(), w = read();
	int x;
	for(int i = 1; i <= n; ++i) {
		x = read();
		for(int j = 0; j < x; ++j)
			v[i].push_back(read());
		l = 0, r = 0;
		qu[0].l = 0, qu[0].r = 0;
		int pre = 0, now;
		for(int j = 1; j <= w; ++j) {
			int L = j - (w - x);
			while(L > qu[l].r && l <= r)
				l++;
			if(j <= x) {
				while(v[i][j - 1] > qu[r].l && l <= r)
					r--;
				qu[++r].l = v[i][j - 1], qu[r].r = j;
			}
			else if(j == x + 1) {
				while(0 > qu[r].l && l <= r)
					r--;
				qu[++r].l = 0, qu[r].r = j;
			}
			now = (l <= r ? qu[l].l : 0);
			s[j] += now - pre;
			pre = now;
			if(L < 0 && j > x)
				j = j - L - 1;
			if(l > r)
				break;
		}
	}
	for(int i = 1; i <= w; ++i) {
		s[i] = s[i - 1] + s[i];
		printf("%lld ", s[i]);
	}
			
	return 0;
}
