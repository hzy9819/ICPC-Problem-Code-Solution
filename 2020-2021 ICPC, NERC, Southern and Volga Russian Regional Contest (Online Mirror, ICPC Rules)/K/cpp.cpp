#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

string s;
pair<int, int> obs;

bool check() {
	if(obs == mk(0, 0))
		return false;
	pair<int, int> pos, to;
	pos = mk(0, 0);
	for(size_t i = 0; i < s.size(); ++i) {
		if(s[i] == 'U')
			to = mk(pos.l, pos.r + 1);
		else if(s[i] == 'D')
			to = mk(pos.l, pos.r - 1);
		else if(s[i] == 'L')
			to = mk(pos.l - 1, pos.r);
		else
			to = mk(pos.l + 1, pos.r);
		if(to == obs)
			continue;
		pos = to;
	}
	return pos == mk(0, 0);
}

int main() {
	int T = read();
	while(T--) {
		cin >> s;
		obs = mk(5000, 5000);
		if(check()) {
			printf("%d %d\n", obs.l, obs.r);
			continue;
		}
		pair<int, int> pos, to;
		bool fg = 0;
		pos = mk(0, 0);
		for(size_t i = 0; i < s.size(); ++i) {
			if(s[i] == 'U')
				to = mk(pos.l, pos.r + 1);
			else if(s[i] == 'D')
				to = mk(pos.l, pos.r - 1);
			else if(s[i] == 'L')
				to = mk(pos.l - 1, pos.r);
			else
				to = mk(pos.l + 1, pos.r);
			obs = to;
			if(check()) {
				printf("%d %d\n", obs.l, obs.r);
				fg = 1;
				break;
			}
			pos = to;
		}
		if(!fg)
			puts("0 0");
	}
	return 0;
}
