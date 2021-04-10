#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define sz(a) ((int) (a).size())
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 500010;
const int S = 27;
const int MAG = 500;

struct Node {
	Node * to[S];
	int num;
}nd[N];
int sz = 0;

typedef Node * vt;

vt getNode() {
	for(int i = 0; i < S; ++i)
		nd[sz].to[i] = NULL;
	nd[sz].num = 0;
	return & nd[sz++];
}

void add(vt v, const string & s) {
	for(int i = 0; i < sz(s); ++i) {
		int c = s[i] - 'a';
		if(v->to[c] == NULL)
			v->to[c] = getNode();
		v = v->to[c];
	}
	v->num++;
}

int calc(vt v, const string & s, int pos) {
	int res = 0;
	while(pos < sz(s)) {
		int c = s[pos] - 'a';
		if(v->to[c] == NULL)
			break;
		v = v->to[c];
		res += v->num;
		pos++;
	}
	return res;
}

vector <int> Count(string s) {
	vector <int> z(sz(s), 0);
	for(int i = 1, l = 0, r = 0; i < sz(s); ++i) {
		if(i < r)
			z[i] = min(r - i, z[i - l]);
		while(i + z[i] < sz(s) && s[i + z[i]] == s[z[i]])
			z[i]++;

		if(i + z[i] > r)
			l = i, r = i + z[i];
	}
	return z;
}

string t;
int n;
vector<string> s;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int main() {
	cin >> t;
	n = read();
	s.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> s[i];
	vector <int> ct[2];
	for(int cur = 0; cur < 2; ++cur) {
		ct[cur].assign(sz(t) + 1, 0);
		sz = 0;
		vt root = getNode();
		for(int i = 0; i < n; ++i) {
			if(sz(s[i]) > MAG) {
				vector <int> cc = Count(s[i] + t);
				for(int j = 0; j < sz(t); ++j)
					ct[cur][j] += (cc[sz(s[i]) + j] >= sz(s[i]));
			}
			else
				add(root, s[i]);
		}

		for(int i = 0; i < sz(t); ++i)
			ct[cur][i] += calc(root, t, i);

		reverse(t.begin(), t.end());
		for(int i = 0; i < n; ++i)
			reverse(s[i].begin(), s[i].end());
	}

	LL ans = 0;
	for(int i = 0; i < sz(t) + 1; ++i)
		ans += 1LL * ct[0][i] * ct[1][sz(t) - i];
	cout << ans << endl;
	
	return 0;
}
