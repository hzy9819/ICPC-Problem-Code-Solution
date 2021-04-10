#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <Queue>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n, m;
int a[N], ans, ans_num, sum;
bool b[N];
queue <int> Q;

void Update(int t) {
	for(int i = 0; i < n; ++i)
		b[i] = 1;
	int now, res = 0;
	for(int i = n - 1; i >= 0; --i)
		if(b[i] && a[i] < t) {
			while(!Q.empty())
				Q.pop();
			Q.push(i);
			now = t - a[i];
			for(int j = i - 1; j >= 0 && now; --j)
				if(b[j] && a[j] <= now) {
					Q.push(j);
					now = now - a[j];
				}
			if(!now) {
				res++;
				while(!Q.empty()) {
					int tmp = Q.front(); Q.pop();
					b[tmp] = 0;
				}
			}
		}
	if(res > ans_num)
		ans = t, ans_num = res;
}

int main() {
	int T = read();
	while(T--) {
		m = read(), n = read();
		ans = 0, ans_num = 1;
		for(int i = 0; i < n; ++i)
			a[i] = read(), ans += a[i];
		sort(a, a + n);
		sum = ans;
		for(int i = m; ; ++i) {
			if(i * ans_num >= sum)
				break;
			Update(i);
		}
		printf("%d\n", ans);
	}
	return 0;
}
