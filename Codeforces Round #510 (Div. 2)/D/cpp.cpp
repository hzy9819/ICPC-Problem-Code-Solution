#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int inf = 1 << 30;
const LL INF = 1LL << 60;
const int N = 200010;
struct Num {
	Num() {}
	Num(LL _num, int _id) : num(_num), id(_id) {}
	LL num; int id;
	bool operator < (const Num & p) const { return num < p.num; }
}s[N];
LL rk[N], a[N], n, t, ans;
set <Num> S;
int tr[N * 2];
void add(int x, int ad) {
	for(; x > 0; x -= (x & (-x)))
		tr[x] += ad;
}
int Que(int x) {
	int res = 0;
	for(; x <= n + 1; x += (x & (-x)))
		res += tr[x];
	return res;
}

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("D");
	n = read(), t = read();
	for(int i = 1; i <= n; ++i) {
		a[i] = read();
		s[i].id = i;
		s[i].num = s[i - 1].num + a[i];
	}
	s[0].num = 0;
	sort(s, s + n + 1);
	for(int i = 0; i <= n; ++i)
		rk[s[i].id] = i + 1;
	S.insert(s[rk[0] - 1]);
	add(rk[0], 1);
	for(int i = 1; i <= n; ++i) {
		Num tmp = Num(s[rk[i] - 1].num - t, 0);	   
		set<Num>::iterator it = S.upper_bound(tmp);
		if(it == S.end()) {}
		else if(it == S.begin()) {
			ans += i;
		}
		else {
			ans += Que(rk[(*it).id]);
		}
		S.insert(s[rk[i] - 1]);
		add(rk[i], 1);
	}
	cout << ans << endl;
		
	return 0;
}
