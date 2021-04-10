#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 100010;
LL n, m, a, d, t[N], ans;
LL read() {
	LL w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	//Hzy("A");
	n = read(), m = read(), a = read(), d = read();
	for(int i = 1; i <= m; ++i) t[i] = read();
	sort(t + 1, t + m + 1);
	LL now(0), t1, t2, t3, num = d / a + 1, po(0), tmp, tp;
	for(int i = 1; i <= m; ++i) {
		if(t[i] <= now) continue;
		po = now / a;
		if(po >= n) {now = t[i] + d; ans++; continue;}
		//t1 = now % a, t1 = a - t1;
		t1 = (po + 1) * a;
		if(t1 >= t[i]) {
			ans++, now = t[i] + d;
			//tmp = d - (now + t1 - t[i]);
			//if(tmp < 0) tmp = 0;
			//else tmp = d / a + 1;
			//po += tmp;
		}
		else {
			t2 = t[i] / a;
			//t3 = po;;
			if(t2 >= n) {
				tmp = n - po;
				tp = tmp / num;
				if(tmp % num) tp++;
				ans += tp, now = (po + (tp - 1) * num + 1) * a + d;
				if(now < t[i]) ans++, now = t[i] + d;
				//po = n;
			}
			else {
				tmp = (t2 - po);
				tp = tmp / num;
				if(tmp % num) tp++;
				ans += tp, now = (po + (tp - 1) * num + 1) * a + d;
				//po = t3 + tp * num;
			//if(po + tmp > n) tmp = n - po;
			//ans += tmp + 1, now = (po + tmp * num + 1) * a + d;
				if(now >= t[i]) continue;
				ans++, now = t[i] + d;
				//if(po >= n) {now = t[i] + d, ans++; continue;}
			}
		}
	}
	po = now / a;
	if(po < n) {
		ans += (n - po) / num;
		if((n - po) % num) ans++;
	}
	printf("%I64d\n", ans);									
	return 0;
}
