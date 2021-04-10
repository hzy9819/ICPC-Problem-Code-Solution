#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int S = 1000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void GetNext(string & a, int * nxt) {
	int n = a.size();
	nxt[0] = 0;
	for(int i = 1, k = 0; i < n; ++i) {
		while(a[k] != a[i] && k != 0)
			k = nxt[k - 1];
		if(a[k] == a[i])
			k++;
		nxt[i] = k;
	}
}

string s[N], res;
int nxt[S], n;

int main() {
	n = read();
	for(int i = 0; i < n; ++i)
		cin >> s[i];
	res = s[0];
	string tmp;
	for(int i = 1; i < n; ++i) {
		if(s[i].size() <= res.size()) {
			tmp = s[i] + res.substr(res.size() - s[i].size(), s[i].size());
			GetNext(tmp, nxt);
			int k = tmp.size() - 1;
			while(nxt[k] > s[i].size() && k != 0)
				k = nxt[k - 1];
			int L = nxt[k];
			if(L < s[i].size())
				res += s[i].substr(L, s[i].size() - L);
		}
		else {
			tmp = s[i].substr(0, res.size()) + res;
			GetNext(tmp, nxt);
			int L = nxt[tmp.size() - 1];
			if(L >= res.size())
				res = s[i];
			else
				res += s[i].substr(L, s[i].size() - L);
		}
	}
	cout << res << endl;
	return 0;
}
