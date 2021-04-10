#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
bool t1[26], t2[26];
int n;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	Hzy("C");
	memset(t1, 1, sizeof t1);
	n = read();
	LL tot(0), cr(0), cnt(0);
	bool fg = 0;
	char c; string s;
	for(int i = 1; i < n; ++i) {
		//char c; string s;
		cin >> c >> s;
		if(c == '!') {
			memset(t2, 0, sizeof t2);
			for(int j = 0; j < s.size(); ++j)
				t2[s[j] - 'a'] = 1;
			for(int j = 0; j < 26; ++j)
				t1[j] &= t2[j];
		}
		else if(c == '.') {
			for(int j = 0; j < s.size(); ++j)
				t1[s[j] - 'a'] = 0;
		}
		else
			t1[s[0] - 'a'] = 0;
		cnt = 0;
		for(int j = 0; j < 26; ++j)
			if(t1[j]) cnt++;
		if(c == '?' || c == '!') tot++;
		if(cnt == 1 && !fg) {
			fg = 1, cr = tot;
		}
	}
	if(!fg) cr = tot;
	cin >> c >> s;
	cout << tot - cr << endl;
	return 0;
}
