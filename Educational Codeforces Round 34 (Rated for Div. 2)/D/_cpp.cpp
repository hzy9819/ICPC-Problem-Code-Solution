#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 200010;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
int a[N], p[N], sz, t1[N], t2[N], z[N];
map<int, int> M;
LL s[N];
struct Num {
	LL a, b;
}ans;
const LL weg = (1e+17);
void add(LL t) {
	if(t > 0) {
		ans.a += (ans.b + t) / weg;
		ans.b = (ans.b + t) % weg;
	}
	else {
		ans.b += t;
		if(ans.b < 0) ans.b += weg, ans.a--;
	}
}
void Mo1(int x, int * t, int d) {
	for(; x <= sz; x += (x & (-x))) t[x] += d;
}
void Mo2(int x, int * t, int d) {
	for(; x > 0; x -= (x & (-x))) t[x] += d;
}
int Que1(int x, int * t) {
	if(x > sz) return 0;
	int res = 0;
	for(; x <= sz; x += (x & (-x))) res += t[x];
	return res;
}
int Que2(int x, int * t) {
	if(x <= 0) return 0;
	int res = 0;
	for(; x > 0; x -= (x & (-x))) res += t[x];
	return res;
}

int main() {
	Hzy("D");
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read(), p[i] = a[i];
	for(int i = n; i >= 1; --i) s[i] = s[i + 1] + a[i];
	int tp = 0;
	sort(p + 1, p + n + 1);
	//for(int i = 1; i <= n; ++i) if(p[i] != p[i + 1]) p[++tp] = p[i];
	int tmp;
	for(int i = 1; i <= n; ++i)
		if(p[i] != p[i - 1]) sz++, M[p[i]] = sz;
	for(int i = 1; i <= n; ++i) if(p[i] != p[i + 1]) p[++tp] = p[i];
	for(int i = 1; i <= n; ++i) {
		tmp = M[a[i]];
		Mo1(sz - tmp + 1, t1, 1), Mo1(tmp, t2, 1);
		z[tmp]++;
	}
	int x, y;
	for(int i = 1; i <= n; ++i) {
		tmp = M[a[i]];
		Mo1(sz - tmp + 1, t1, -1), Mo1(tmp, t2, -1), z[tmp]--;
		if(tmp == sz || p[tmp + 1] != p[tmp] + 1) x = 0;
		else x = Que2(sz - (tmp + 1) + 1, t1) - Que2(sz -(tmp + 2) + 1, t1);
		/*if(tmp == sz || p[tmp + 1] != p[tmp] + 1) x = 0;
		  else x = p1 - Que1(tmp + 1, t1);*/
		//p2 = Que2(tmp, t2);
		if(tmp == 1 || p[tmp - 1] != p[tmp] - 1) y = 0;
		else y = Que2(tmp - 1, t2) - Que2(tmp - 2, t2);
		
		add(s[i] - 1LL * (n - i + 1) * a[i]);
		add(-x), add(y);
		//ans -= x, ans += y;
	}
	//printf("%I64d\n", ans);
	if(!ans.a) printf("%I64d\n", ans.b) ;
	else {
		if(ans.a < 0) {
			if(ans.a == -1)  printf("%I64d\n", ans.b - weg);
			else printf("%I64d%017I64d\n", ans.a + 1, abs(ans.b - weg));
		}
		else 
			printf("%I64d%017I64d\n", ans.a, ans.b);
	}
	//printf("%012d", 100);
	return 0;
}
