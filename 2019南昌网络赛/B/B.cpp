#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define FOR(a,b,c) for(int a=b;a<=c;a++)
#define FORD(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template<class T>inline void Max(T &a,T b)
{
 if(b > a) a = b;
}

template<class T>inline void Min(T &a,T b)
{
 if(b < a) a = b;
}
template<class T>void rd(T &x)
{
 x = 0;
 char c;
 while (c = getchar(), c < '0');
 do
 {
  x = x * 10 + (c^'0');
 }
 while(c = getchar(), c >= '0');
}
struct pt {
	int dis, x;
	pt(int _x, int _dis) {
		x = _x;
		dis = _dis;
	}
};
bool operator <(pt x, pt y) {
	return x.dis > y.dis;
}
priority_queue<pt> q;
int Enum, F[1010], N[1000010], V[1000010], W[1000010];
inline void addedge(int x, int y, int z) {
	V[++Enum] = y;
	W[Enum] = z;
	N[Enum] = F[x];
	F[x] = Enum;
}
int T, n, m, s, k, c;
int dis[1010];
bool bl[1010];
void calc(int n, int S) {
	FOR(i, 1, n) dis[i] = 1000000000;
	FOR(i, 1, n) bl[i] = 0;
	dis[S] = 0;
	q.push(pt(S, 0));
	while (!q.empty()) {
		pt h = q.top();
		q.pop();
		if (bl[h.x]) continue;
		bl[h.x] = 1;
		for (int now = F[h.x]; now; now = N[now]) {
			if (dis[V[now]] > dis[h.x] + W[now]) {
				dis[V[now]] = dis[h.x] + W[now];
				q.push(pt(V[now], dis[V[now]]));
			}
		}	
	}
}
int f_p[1010];
int tmp_min[1010];
int x, y, z;
int hero_max, f_p_max;
int main() {
	scanf("%d", &T);
	while (T--) {
		rd(n);
		rd(m);
		rd(s);
		rd(k);
		rd(c);
		FOR(i, 1, k) rd(f_p[i]);
		FOR(i, 1, m) {
			rd(x);
			rd(y);
			rd(z);
			addedge(x, y, z);
			addedge(y, x, z);
		}
		calc(n, s);
		hero_max = 0;
		f_p_max = 0;
		FOR(i, 1, n) tmp_min[i] = 1000000000;
		FOR(i, 1, n) Max(hero_max, dis[i]);
		FOR(i, 1, k) {
			calc(n, f_p[i]);
			FOR(j, 1, n) if (j != f_p[i]) Min(tmp_min[j], dis[j]);
		}
		FOR(i, 1, n) Max(f_p_max, tmp_min[i]);
		if (hero_max <= f_p_max * c) printf("%d\n", hero_max);
		else printf("%d\n", f_p_max);
		FOR(i, 1, n) F[i] = 0;
		FOR(i, 1, Enum) V[i] = N[i] = W[i] = 0;
		Enum = 0;
	}
	return 0;
}