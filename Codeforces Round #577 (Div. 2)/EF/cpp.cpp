#include <bits/stdc++.h>
#define LL long long
#define db double
#define mk(a, b) make_pair(a, b)
#define l first
#define r second
#define islegal(x) ((x).l <= n && (x).r <= m && (x).l > 0 && (x).r > 0)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 1010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
int n, m, disw[N][N], disb[N][N];
pair <int, int> w, b, gw, gb;

queue <pair<int, int> > Q;

void bfs(int dis[N][N]) {
	pair <int, int> tmp, temp;
	while(!Q.empty()) {
		tmp = Q.front(); Q.pop();
		for(int i = 0; i < 8; ++i) {
			temp.l = tmp.l + dx[i], temp.r = tmp.r + dy[i];
			if(islegal(temp) && dis[temp.l][temp.r] == 0) {
				dis[temp.l][temp.r] = dis[tmp.l][tmp.r] + 1;
				Q.push(temp);
			}
		}
	}
}

int main() {
	n = read(), m = read();
	w.l = read(), w.r = read(), b.l = read(), b.r = read();
	disw[n / 2][m / 2] = 1, disb[n / 2 + 1][m / 2] = 1;
	gw = mk(n / 2, m / 2), gb = mk(n / 2 + 1, m / 2);
	Q.push(gw);
	bfs(disw);
	Q.push(gb);
	bfs(disb);

	pair<int, int> tmp;

	if(disw[w.l][w.r] + 1 <= disw[b.l][b.r] && disw[w.l][w.r] <= disb[b.l][b.r]) {
		puts("WHITE");
		fflush(stdout);
		while(w != gw) {
			for(int i = 0; i < 8; ++i) {
				tmp.l = w.l + dx[i], tmp.r = w.r + dy[i];
				if(islegal(tmp) && disw[tmp.l][tmp.r] < disw[w.l][w.r]) {
					w = tmp;
					printf("%d %d\n", w.l, w.r);
					fflush(stdout);
					if(w == b)
						return 0;
					if(w != gw)
						b.l = read(), b.r = read();
					break;
				}
			}
		}
	}
	else if(disb[b.l][b.r] + 2 <= disb[w.l][w.r] && disb[b.l][b.r] + 1 <= disw[w.l][w.r]) {
		puts("BLACK");
		fflush(stdout);
		w.l = read(), w.r = read();
		while(b != gb) {
			for(int i = 0; i < 8; ++i) {
				tmp = mk(b.l + dx[i], b.r +dy[i]);
				if(islegal(tmp) && disb[tmp.l][tmp.r] < disb[b.l][b.r]) {
					b = tmp;
					printf("%d %d\n", b.l, b.r);
					fflush(stdout);
					if(w == b)
						return 0;
					if(b != gb)
						w.l = read(), w.r = read();
					break;
				}
			}
		}
	}
	else if((w.l + w.r) % 2 != (b.l + b.r) % 2) {
		puts("WHITE");
		fflush(stdout);
		if(disw[w.l][w.r] <= disb[b.l][b.r]) {
			while(w != gw) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(w.l + dx[i], w.r + dy[i]);
					if(islegal(tmp) && disw[tmp.l][tmp.r] < disw[w.l][w.r]) {
						w = tmp;
						printf("%d %d\n", w.l, w.r);
						fflush(stdout);
						if(w == b)
							return 0;
						if(w != gw)
							b.l = read(), b.r = read();
						break;
					}
				}
			}
		}
		else {
			while(w != gb) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(w.l + dx[i], w.r + dy[i]);
					if(islegal(tmp) && disb[tmp.l][tmp.r] < disb[w.l][w.r]) {
						w = tmp;
						printf("%d %d\n", w.l, w.r);
						fflush(stdout);
						if(w == b)
							return 0;
						b.l = read(), b.r = read();
						break;
					}
				}
			}
			for(int i = 0; i < 8; ++i) {
				tmp = mk(w.l + dx[i], w.r + dy[i]);
				if(b == tmp) {
					printf("%d %d\n", tmp.l, tmp.r);
					fflush(stdout);
					return 0;
				}
			}
			while(w != gw) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(w.l + dx[i], w.r + dy[i]);
					if(islegal(tmp) && disw[tmp.l][tmp.r] < disw[w.l][w.r]) {
						w = tmp;
						printf("%d %d\n", w.l, w.r);
						fflush(stdout);
						if(w == b)
							return 0;
						if(w != gw)
							b.l = read(), b.r = read();
						break;
					}
				}
			}
		}
	}
	else {
		puts("BLACK");
		fflush(stdout);
		w.l = read(), w.r = read();
		if(disw[w.l][w.r] >= disb[b.l][b.r]) {
			while(b != gb) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(b.l + dx[i], b.r +dy[i]);
					if(islegal(tmp) && disb[tmp.l][tmp.r] < disb[b.l][b.r]) {
						b = tmp;
						printf("%d %d\n", b.l, b.r);
						fflush(stdout);
						if(w == b)
							return 0;
						if(b != gb)
							w.l = read(), w.r = read();
						break;
					}
				}
			}
		}
		else {
			while(b != gw) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(b.l + dx[i], b.r + dy[i]);
					if(islegal(tmp) && disw[tmp.l][tmp.r] < disw[b.l][b.r]) {
						b = tmp;
						printf("%d %d\n", b.l, b.r);
						fflush(stdout);
						if(w == b)
							return 0;
						w.l = read(), w.r = read();
						break;
					}
				}
			}
			for(int i = 0; i < 8; ++i) {
				tmp = mk(b.l + dx[i], b.r + dy[i]);
				if(tmp == w) {
					printf("%d %d\n", w.l, w.r);
					fflush(stdout);
					return 0;
				}
			}
			while(b != gb) {
				for(int i = 0; i < 8; ++i) {
					tmp = mk(b.l + dx[i], b.r +dy[i]);
					if(islegal(tmp) && disb[tmp.l][tmp.r] < disb[b.l][b.r]) {
						b = tmp;
						printf("%d %d\n", b.l, b.r);
						fflush(stdout);
						if(w == b)
							return 0;
						if(b != gb)
							w.l = read(), w.r = read();
						break;
					}
				}
			}
		}
	}
	
	return 0;
}
