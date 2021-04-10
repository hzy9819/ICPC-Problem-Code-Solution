#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 500010;
const int Sz = 710;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

vector <int> v[Sz];
int q, a[N];

int main() {
	int typ, x, y, sum;
	for(int i = 1; i < Sz; ++i)
		for(int j = 0; j < i; ++j)
			v[i].push_back(0);
	q = read();
	for(int i = 1; i <= q; ++i) {
		typ = read(), x = read(), y = read();
		if(typ == 1) {
			a[x] += y;
			for(int j = 1; j < Sz; ++j)
				v[j][x % j] += y;
		}
		else {
			if(x < Sz)
				sum = v[x][y];
			else {
				sum = 0;
				for(int j = y; j <= 500000; j += x)
					sum += a[j];
			}
			cout << sum << endl;
		}
	}
	return 0;
}
