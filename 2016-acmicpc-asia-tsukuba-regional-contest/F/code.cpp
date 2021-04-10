#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#define LL long long
#define db double
#define ULL unsigned long long
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;
const int N = 310;
const int M = 1010;
ULL bin[65];
struct Edge {
	int x, y;
};
struct Fl {
	vector <Edge> v;
}s[M];
struct St {
	ULL a[5];
	St() {
		a[0] = a[1] = a[2] = a[3] = a[4] = 0;
	}
	void del(int k) {
		if(a[(k - 1) / 64] & bin[k % 64]) 
			a[(k - 1) / 64] ^= bin[k % 64];
	}
	void add(int k) {
		a[(k - 1) / 64] |= bin[k % 64];
	}
	bool Mx(const St & p) const {
		bool fg = 0;
		for(int i = 0; i < 5; ++i)
			if(a[i] & p.a[i]) {
				fg = 1;
				break;
			}
		return fg;
	}
	bool In(int k) {
		return a[(k - 1) / 64] & bin[k % 64];
	}
};
void IM() {
	puts("No");
	exit(0);
}
St f[M][3]; // 0 means no, 1 means is son, 2 means is fa
vector <int> g[M][M];
string a[M];
int n, cnt;
bool u[M], us[M][M];
queue <int> Q;
int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
void Spread(int x, int y) {
	us[x][y] = 1;
	for(int i = 0; i < g[x][y].size(); ++i)
		if(!u[g[x][y][i]]) {
			Q.push(g[x][y][i]);
			u[g[x][y][i]] = 1;
		}
}
void Update() {
	for(int i = 1; i <= cnt; ++i)
		for(int j = 1; j <= cnt; ++j) {
			if(!us[i][j]) {
				int st = 0;
				if(f[i][1].Mx(f[j][2]) || f[i][1].In(j)) st |= 1;
				if(f[i][2].Mx(f[j][1]) || f[j][1].In(i)) st |= 2;
				if(st == 3 || (st && i == j)) IM();
				if(st == 1) f[i][1].add(j), f[j][2].add(i), Spread(i, j);
				if(st == 2) f[i][2].add(j), f[j][1].add(i), Spread(j, i);
				//if(st) f[i][0].del(j), f[j][0].del(i);
			}
		}
}
				

int main() {
	//Hzy("F");
	string tmp;
	int k, t, x, y;
	cin >> tmp;
	cnt = 1;
	a[1] = tmp;
	cin >> tmp;
	if(a[1] == tmp) IM();
	a[++cnt] = tmp;
	n = read();
	bin[0] = 1;
	for(int i = 1; i <= 63; ++i) bin[i] = (bin[i - 1] << 1);
	Edge temp;
	for(int i = 1; i <= n; ++i) {
		t = read();
		for(int j = 1; j <= t; ++j) {
			int k;
			cin >> tmp;
			for(k = 1; k <= cnt; ++k)
				if(tmp == a[k]) break;
			if(k > cnt) a[++cnt] = tmp;
			x = k;
			cin >> tmp;
			for(k = 1; k <= cnt; ++k)
				if(tmp == a[k]) break;
			if(k > cnt) a[++cnt] = tmp;
			y = k;
			if(x == y) IM();
			temp.x = x, temp.y = y;
			s[i].v.push_back(temp);
			g[x][y].push_back(i);
		}
	}
	/*if(x > cnt || y > cnt) {
		puts("Yes");
		return 0;
		}*/
	f[1][1].add(2), f[2][2].add(1);
	Spread(1, 2);
	while(!Q.empty()) {
		while(!Q.empty()) {
			k = Q.front(), Q.pop();
			for(int i = 0; i < s[k].v.size(); ++i) {
				x = s[k].v[i].x, y = s[k].v[i].y;
				if(f[x][2].In(y)) IM();
				else {
					//f[x][0].del(y);
					f[x][1].add(y);
				}
				if(f[y][1].In(x)) IM();
				else {
					//f[y][0].del(x);
					f[y][2].add(x);
				}
			}
		}
		Update();
	}
	puts("Yes");
	return 0;
}
