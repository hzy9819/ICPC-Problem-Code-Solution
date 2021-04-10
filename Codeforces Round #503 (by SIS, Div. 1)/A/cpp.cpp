#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 3010;
struct Voter {
	int to, p, id;
	bool operator < (const Voter & tp) const {
		return p < tp.p;
	}
}a[N];
vector <Voter> v[N];
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
bool us[N];
LL ans = INF;

int main() {
	Hzy("A");
	n = read(), m = read();
	int to, py;
	for(int i = 1; i <= n; ++i) {
		to = read(), py = read();
		a[i].to = to, a[i].p = py, a[i].id = i;
		v[to].push_back(a[i]);
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= m; ++i)
		sort(v[i].begin(), v[i].end());
	for(int i = 1; i <= n; ++i) {
		memset(us, 0, sizeof us);
		int ct = 0;
		LL temp = 0;
		for(int j = 2; j <= m; ++j)
			if(v[j].size() >= i) {
				for(int k = 0; k <= v[j].size() - i; ++k)
					ct++, us[v[j][k].id] = 1, temp += v[j][k].p;
			}
		int cnt = 1;
		while(ct + v[1].size() < i) {
			if(!us[a[cnt].id] && a[cnt].to != 1)
				ct++, temp += a[cnt].p;
			cnt++;
		}
		ans = min(ans, temp);
	}
	cout << ans << endl;
	return 0;
}
