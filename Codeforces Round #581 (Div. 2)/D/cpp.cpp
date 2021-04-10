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

int main()  {
	cin >> s;
	int now = 0;
	for(int i = s.size() - 1; i >= 0; --i) {
		if(s[i] == '0')
			now++;
		else if(now)
			now--;
		else
			s[i] = '0';
	}
	cout << s << endl;
	return 0;
}
