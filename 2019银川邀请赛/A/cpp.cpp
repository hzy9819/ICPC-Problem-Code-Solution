#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 5000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, p, q, m;
unsigned int SA, SB, SC;
unsigned int rng61() {
	SA ^= SA << 16;
	SA ^= SA >> 5;
	SA ^= SA << 1;
	unsigned int t = SA; SA = SB;
	SB = SC;
	SC ^= t ^ SA;
	return SC;
}

unsigned int sta[N], res[N], top;
LL ans;


int main() {
	int T = read(), tc = 0;
	while(T--) {
		tc++;
		n = read(), p = read(), q = read(), m = read(), SA = read(), SB = read(), SC = read();
		top = 0;
		ans = 0;
		for(int i = 1; i <= n; ++i) {
			int type = (rng61() % (p + q) < p);
			if(type) {
				unsigned int tmp = rng61() % m + 1;
				sta[++top] = tmp;
				res[top] = max(res[top - 1], sta[top]);
			}
			else {
				if(top)
					top--;
			}
			ans ^= 1LL * i * res[top];
		}
		cout << "Case #" << tc << ": " << ans << endl;
	}
	return 0;
}
