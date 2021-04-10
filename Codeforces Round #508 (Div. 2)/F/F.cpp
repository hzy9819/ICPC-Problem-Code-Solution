#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 50;
LL f[N][N][N][2], tp[N][N], ans;
string s;
int n, m;

void Init() {
	for(int i = 0; i <= m; ++i)
		for(char j = '0'; j <= '1'; ++j)
			for(int k = min(i, m - 1); k >= 0; k--) {
				string tmp = s.substr(i - k, k) + j;
				if(s.substr(0, k + 1) == tmp) {
					tp[i][j - '0'] = k + 1;
					break ;
				}
			}
	memset(f, -1, sizeof f);
}

LL calc(int t, int suf, int pre, bool ok) {
	if(t == n) 
		return (suf == pre) && ok;
	if(f[t][suf][pre][ok] != -1) return f[t][suf][pre][ok];
	return f[t][suf][pre][ok] = calc(t + 1, tp[suf][0], pre, ok || tp[suf][0] == m) + calc(t + 1, tp[suf][1], pre, ok || tp[suf][1] == m);
}

int main() {
	Hzy("F");
	cin >> n >> s;
	m = s.size();
	Init();
	for(int i = 0; i <= m; ++i)
		ans += calc(0, i, i, i == m);
	cout << ans << endl;
}
