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

vector <pair<int, int> > ans;

int main() {
	cin >> s;
	int x, y;
	x = y = 0;
	int len = 1;
	size_t n = s.size();
	if(n >= 3) {
		string t = s.substr(n - 3);
		if(t == "LRL" || t == "RLR" || t == "UDU" || t == "DUD") {
			puts("impossible");
			return 0;
		}
	}
	for(size_t i = 0; i < n; ++i) {
		if(s[i] == 'L') {
			x = -len;
			ans.push_back(mk(x - 1, y));
		}
		else if(s[i] == 'R') {
			x = len;
			ans.push_back(mk(x + 1, y));
		}
		else if(s[i] == 'U') {
			y = len;
			ans.push_back(mk(x, y + 1));
		}
		else if(s[i] == 'D') {
			y = -len;
			ans.push_back(mk(x, y - 1));
		}

		if(i + 1 < n) {
			string t = s.substr(i, 2);
			if(t == "LR" || t == "RL" || t == "UD" || t == "DU")
				continue;
			len += 4;
		}
	}
	for(size_t i = 0; i < ans.size(); ++i)
		ans[i].l -= x, ans[i].r -= y;
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	printf("%d %d\n", -x, -y);
	//printf("%llu\n", ans.size());
	cout << ans.size() << endl;
	for(size_t i = 0; i < ans.size(); ++i)
		printf("%d %d\n", ans[i].l, ans[i].r);
			

	return 0;
}
