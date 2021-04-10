#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
const int INF = 1 << 30;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n, m, k, q, l[N], r[N], b[N];

pair <int, int> pos[N];

LL f[N][2];

LL calc(int l, int r, int pos, int type) { // l: 0, r : 1
	if(type) {
		if(pos >= r)
			return pos - l + (r - 1);
		if(pos <= l)
			return r - pos;
		return r - pos + 2 * (pos - l);
	}
	else {
		if(pos <= l)
			return r - pos + (r - l);
		if(pos >= r)
			return pos - l;
		return pos - l + 2 * (r - pos);
	}
}

int Pre(int * a, int n, int p) {
	int l = 0, r = n - 1, mid, res;
	for(mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		if(a[mid] > p) r = mid - 1;
		else l = mid + 1, res = mid;
	return a[res];
}

int Nxt(int * a, int n, int p) {
	int l = 0, r = n - 1, mid, res;
	for(mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		if(a[mid] < p) l = mid + 1;
		else r = mid - 1, res = mid;
	return a[res];
}

int main() {
	Hzy("D");
	n = read(), m = read(), k = read(), q = read();
	for(int i = 0; i < k; ++i)
		pos[i].first = read(), pos[i].second = read();
	sort(pos, pos + k);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		while(cnt < k && pos[cnt].first < i)
			cnt++;
		l[i] = m + 1, r[i] = 0;
		while(cnt < k && pos[cnt].first == i)
			l[i] = min(l[i], pos[cnt].second), r[i] = max(r[i], pos[cnt].second), cnt++;
	}
	for(int i = 0; i < q; ++i)
		b[i] = read();
	sort(b, b + q);
	while(r[n] == 0) n--;
	
	if(r[1] != 0) {
		f[1][0] = calc(l[1], r[1], 1, 0);
		f[1][1] = calc(l[1], r[1], 1, 1);
	}
	else l[1] = r[1] = 1;

	LL tmp[2][2], t;	
	for(int i = 2; i <= n; ++i) {
		if(r[i] == 0) {
			l[i] = l[i - 1], r[i] = r[i - 1];
			f[i][0] = f[i - 1][0] + 1, f[i][1] = f[i - 1][1] + 1;
		}
		else {
			tmp[0][0] = tmp[0][1] = tmp[1][0] = tmp[1][1] = INF;
			if(l[i - 1] >= b[0]) {
				t = Pre(b, q, l[i - 1]);
				tmp[0][0] = calc(l[i], r[i], t, 0) + l[i - 1] - t;
				tmp[0][1] = calc(l[i], r[i], t, 1) + l[i - 1] - t;
			}
			if(l[i - 1] <= b[q - 1]) {
				t = Nxt(b, q, l[i - 1]);
				tmp[1][0] = calc(l[i], r[i], t, 0) + t - l[i - 1];
				tmp[1][1] = calc(l[i], r[i], t, 1) + t - l[i - 1];
			}
			f[i][0] = f[i - 1][0] + min(tmp[0][0], tmp[1][0]);
			f[i][1] = f[i - 1][0] + min(tmp[0][1], tmp[1][1]);

			tmp[0][0] = tmp[0][1] = tmp[1][0] = tmp[1][1] = INF;
			if(r[i - 1] >= b[0]) {
				t = Pre(b, q, r[i - 1]);
				tmp[0][0] = calc(l[i], r[i], t, 0) + r[i - 1] - t;
				tmp[0][1] = calc(l[i], r[i], t, 1) + r[i - 1] - t;
			}
			if(r[i - 1] <= b[q - 1]) {
				t = Nxt(b, q, r[i - 1]);
				tmp[1][0] = calc(l[i], r[i], t, 0) + t - r[i - 1];
				tmp[1][1] = calc(l[i], r[i], t, 1) + t - r[i - 1];
			}
			f[i][0] = min(f[i][0], f[i - 1][1] + min(tmp[0][0], tmp[1][0])) + 1;
			f[i][1] = min(f[i][1], f[i - 1][1] + min(tmp[0][1], tmp[1][1])) + 1;
		}
	}
	cout << min(f[n][0], f[n][1]) << endl;						
	return 0;
}
