#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <time.h>
#define LL long long
#define db double
//#define Cmp(t) (fabs(t) < eps ? 0 : (t) < 0 ? -1 : 1)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 70;
const int L = 2;
const int R = 1e9;
db eps = 1e-11;

inline int Cmp(db t) {
	if(fabs(t) < eps) return 0;
	return t < 0 ? -1 : 1;
}

LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int Mu[N], prime[N], cnt;
bool vis[N];

void Init() {
	memset(vis, 0, sizeof vis);
	Mu[1] = 1;
	cnt = 0;
	for(int i = 2; i < N; ++i) {
		if(!vis[i]) {
			prime[cnt++] = i;
			Mu[i] = -1;
		}
		for(int j = 0; j < cnt && i * prime[j] < N; ++j) {
			vis[i * prime[j]] = 1;
			if(i % prime[j]) Mu[i * prime[j]] = -Mu[i];
			else {
				Mu[i * prime[j]] = 0;
				break;
			}
		}
	}
}

LL Fst_pow(LL a, int b) {
	LL ans = 1;
	while(b) {
		if(b & 1) ans *= a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

inline int calc(LL t, int mi) {
	//if(mi == 1) return t;
	if(mi == 2) return sqrt(t);
	if(mi >= 64) return 1;
	if((1LL << mi) > t) return 1;
	int l, r, mid;
	db temp = log(t);
	int tp = pow(t, 1.0 / mi);
	l = max(2, tp - 16), r = tp + 16;
	for(mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
		//LL tmp = Fst_pow(mid, mi);
		//int tmp = temp / log(mid);
		if(((db) mi * log(mid) - temp) > eps) r = mid - 1;
		else l = mid + 1;
	}
	return l - 1;
}

int T;
LL n, ans;

int main() {
	clock_t begin = clock();
	Hzy("F");
	T = read();
	Init();
	while(T--) {
		n = read();
		ans = (n - 1) * Mu[1];
		for(int i = 2; ; ++i) {
			if(!Mu[i]) continue;
			LL tmp = calc(n, i);			
			if(tmp <= 1) break;
			ans += (tmp - 1) * Mu[i];
		}
		printf("%lld\n", ans);
	}
	cout << clock() - begin ;
	return 0;
}
			
