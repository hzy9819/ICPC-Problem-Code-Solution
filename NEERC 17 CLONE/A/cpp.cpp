#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 2000010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
int n;
struct Que{
    int typ, x, y, id;
}Q[N];

int x[N], a[N << 2], id[N << 2];
void PushUp(int u){
    a[u] = max(a[u << 1], a[(u << 1) + 1]);
}
void Build(int u, int l, int r){
    a[u] = 0;
    if(l == r){
        return;
    }
    int mid = (l + r) >> 1;
    Build(2 * u, l, mid);
    Build(2 * u + 1, mid + 1, r);
}
void Update(int u, int pos, int l, int r, int _) {
    if(pos > r || pos < l) return;
    if(l == r){
        id[u] = _;
        a[u] = Q[_].y;
        return ;
    }
    int mid = (l + r) >> 1;
    Update(2 * u, pos, l, mid, _);
    Update(2 * u + 1, pos, mid + 1, r, _);
    PushUp(u);
}
int Ql(int u, int ql, int qr, int l, int r, int _) {
    if(qr < l || ql > r || a[u] * 2 <= Q[_].y) return 0;
    if(l == r) {
        if(1LL * (Q[id[u]].x - Q[_].x) * (Q[id[u]].x - Q[_].x) + 1LL * (Q[id[u]].y - Q[_].y) * (Q[id[u]].y - Q[_].y) < 1LL * Q[id[u]].y * Q[id[u]].y) {
            printf("%d\n", id[u]);
            id[u] = 0;
            a[u] = 0;
            return 1;
        }
        return -1;
    }
    int mid = (l + r) >> 1;
    int ret1 = Ql((u << 1) + 1, ql, qr, mid + 1, r, _);
    int ret = 0;
    if(ret1 == 1) ret = 1;
    else if(ret1 == -1) ret = -1;
    else ret = Ql(u << 1, ql, qr, l, mid, _);
    PushUp(u);
    return ret;
}
int Qr(int u, int ql, int qr, int l, int r, int _){
    if(qr < l || ql > r || a[u] * 2 <= Q[_].y) return 0;
    if(l == r){
        if(1LL * (Q[id[u]].x - Q[_].x) * (Q[id[u]].x - Q[_].x) + 1LL * (Q[id[u]].y - Q[_].y) * (Q[id[u]].y - Q[_].y) < 1LL * Q[id[u]].y * Q[id[u]].y) {
            printf("%d\n", id[u]);
            id[u]=0;
            a[u]=0;
            return 1;
        }
        return -1;
    }
    int mid = (l + r) >> 1;
    int ret1 = Qr(u << 1, ql, qr, l, mid, _);
    int ret = 0;
    if(ret1 == 1) ret = 1;
    else if(ret1 == -1) ret = -1;
    else ret = Qr((u << 1) + 1, ql, qr, mid + 1, r, _);
    PushUp(u);
    return ret;
}
int main() {
	Hzy("A");
    n = read();
    for(int i = 1;i <= n; i++){
		Q[i].typ = read(), Q[i].x = read(), Q[i].y = read();
        Q[i].id = i, x[i] = Q[i].x;
    }
	sort(x + 1, x + n + 1);
    Build(1, 1, n);
	for(int i = 1; i <= n; ++i) {
		if(Q[i].typ == 1) {
			int pos = lower_bound(x + 1, x + n + 1, Q[i].x) - x;
			Update(1, pos, 1, n, i);
		}
		else {
			int pos = lower_bound(x + 1, x + n + 1, Q[i].x) - x;
			if(Ql(1, 1, pos, 1, n, i) != 1 && Qr(1, pos, n, 1, n, i) != 1) {
				puts("-1");
			}
		}
	}
	return 0;    
}
