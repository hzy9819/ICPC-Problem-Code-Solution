#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 55;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int n;
int a[N][N], b[N][N];

int ask(int x1, int y1, int x2, int y2) {
	printf("? %d %d %d %d\n", x1, y1, x2, y2);
	fflush(stdout);
	int tmp;
	scanf("%d", &tmp);
	return tmp;
}

void Ans(int res) {
	puts("!");
	if(res == 1) {
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				printf("%d", a[i][j]);
				if(j == n)
					puts("");
			}
	}
	else {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				printf("%d", b[i][j]);
				if(j == n)
					puts("");
			}
		}
	}
}

bool check(vector <int> & v) {
	vector <int> tmp = v;
	reverse(tmp.begin(), tmp.end());
	for(size_t i = 0; i < v.size(); ++i)
		if(v[i] != tmp[i]) return 0;
	return 1;
}

int tx = -1, ty, sx, sy;
bool r1, r2;
vector <int> p1, p2;
void work(int t, int x, int y) {
	if(!t) {
		bool b1 = check(p1), b2 = check(p2);
		if(b1 != b2) {
			tx = x, ty = y;
			r1 = b1, r2 = b2;
		}
		return ;
	}
	if(tx != -1)
		return ;
	if(x + 1 <= n) {
		p1.push_back(a[x + 1][y]);
		p2.push_back(b[x + 1][y]);
		work(t - 1, x + 1, y);
		p1.pop_back();
		p2.pop_back();
		if(tx != -1)
			return ;
	}
	if(y + 1 <= n) {
		p1.push_back(a[x][y + 1]);
		p2.push_back(b[x][y + 1]);
		work(t - 1, x, y + 1);
		p1.pop_back();
		p2.pop_back();
	}
}

int main() {
	memset(a, -1, sizeof a);
	memset(b, -1, sizeof b);

	n = read();
	for(int i = 1; i <= n; i += 2) {
		for(int j = 1; j <= n; j += 2) {
			if(i == 1 && j == 1) a[i][j] = 1;
			else {
				if(j > 2) a[i][j] = ask(i, j - 2, i, j) ^ a[i][j - 2] ^ 1;
				else a[i][j] = ask(i - 2, j, i , j) ^ a[i - 2][j] ^ 1;
			}
			b[i][j] = a[i][j];
		}
	}
	for(int i = 2; i <= n; i += 2) {
		for(int j = 2; j <= n; j += 2) {
			if(i == 2 && j == 2) a[2][2] = ask(1, 1, 2, 2);
			else {
				if(j > 2) a[i][j] = ask(i, j - 2, i, j) ^ a[i][j - 2] ^ 1;
				else a[i][j] = ask(i - 2, j, i, j) ^ a[i - 2][j] ^ 1;
			}
			b[i][j] = a[i][j];
		}
	}
	for(int i = 1; i <= n; i += 2) {
		for(int j = 2; j <= n; j += 2) {
			if(i == 1 && j == 2) a[1][2] = 0;
			else {
				if(j > 2) a[i][j] = ask(i, j - 2, i, j) ^ a[i][j - 2] ^ 1;
				else a[i][j] = ask(i - 2, j, i, j) ^ a[i - 2][j] ^ 1;
			}
			b[i][j] = a[i][j] ^ 1;
		}
	}
	for(int i = 2; i <= n; i += 2) {
		for(int j = 3; j <= n; j += 2) {
			if(i == 2 && j == 3) a[2][3] = ask(1, 2, 2, 3) ^ a[1][2] ^ 1;
			else {
				if(j > 3) a[i][j] = ask(i, j - 2, i, j) ^ a[i][j - 2] ^ 1;
				else a[i][j] = ask(i - 2, j, i, j) ^ a[i - 2][j] ^ 1;
			}
			b[i][j] = a[i][j] ^ 1;
		}
	}

	for(int i = 2; i <= n; i += 2) {
		a[i][1] = ask(i, 1, i, 3) ^ a[i][3] ^ 1;
		b[i][1] = a[i][1] ^ 1;
	}
	for(int t = 3; tx == -1; ++t) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				p1.clear(), p2.clear();
				p1.push_back(a[i][j]), p2.push_back(b[i][j]);
				work(t, i, j);
				if(tx != -1) {
					sx = i, sy = j;
					break;
				}
			}
			if(tx != -1) break;
		}
	}

	int tmp = ask(sx, sy, tx, ty);
	Ans(tmp == r1);
	return 0;
}
					
			


