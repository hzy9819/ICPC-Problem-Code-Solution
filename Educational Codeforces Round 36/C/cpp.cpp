#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define fast_io() cin.sync_with_stdio(false); cout.sync_with_stdio(false);
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
string a, tmp;
LL b;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int num[10];
int main() {
	fast_io();
	cin >> a >> b;
	sort(a.begin(), a.end());
	for(int i = 0; i < a.size(); ++i) {
		for(int j = i + 1; j < a.size(); ++j) {
			tmp = a;
			swap(tmp[i], tmp[j]);
			sort(tmp.begin() + i + 1, tmp.end());
			if(stoll(tmp) > stoll(a) && stoll(tmp) <= b) swap(a[i], a[j]);
		}
	}
	cout << a;
	return 0;
}
