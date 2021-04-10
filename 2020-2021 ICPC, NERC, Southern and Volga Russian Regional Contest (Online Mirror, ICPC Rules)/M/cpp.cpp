#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define F(o) ((o) * (o) % Size)
#define G(o) (((o) * 114 + 514) % Size)
using namespace std;
const int Size = 22;
const int N = 200010;

set <pair<int, int> > v[25][25];
int n;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

bool check(int x1, int y1, int x2, int y2) {
	if(v[x2][y1].empty() || v[x1][y2].empty() || v[x2][y2].empty())
		return false;
	// cerr << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	pair<int, int> z1, z2, z3, z4;
	// set<pair<int, int> >::iterator it1, it2;
	for(auto it1 = v[x1][y1].begin(); it1 != v[x1][y1].end(); ++it1)
		for(auto it2 = v[x2][y2].begin(); it2 != v[x2][y2].end(); ++it2) {
			// printf("%d %d %d %d\n", it1->l, it1->r, it2->l, it2->r);
			if(it1->l != it2->l && it1->r != it2->r) {
				z2 = *it1;
				z4 = *it2;
				z1 = mk(z2.l, z4.r), z3 = mk(z4.l, z2.r);
				// cerr << "z1: " << z1.l << " " << z1.r << endl;
				// cerr << "z2: " << z2.l << " " << z2.r << endl;
				// cerr << "z3: " << z3.l << " " << z3.r << endl;
				// cerr << "z4: " << z4.l << " " << z4.r << endl;
				if(v[x1][y2].find(z1) != v[x1][y2].end() && v[x2][y1].find(z3) != v[x2][y1].end()) {
					printf("%d %d\n", z2.l, z4.l);
					return true;
				}
			}
		}
	return false;
}

void DEBUG__() {
	for(int i = 0; i < Size; ++i)
		for(int j = 0; j < Size; ++j)
			for(auto it = v[i][j].begin(); it != v[i][j].end(); ++it)
				printf("%d %d\n", it->l, it->r);
}

int main() {
	int T = read();
	while(T--) {
		for(int i = 0; i < Size; ++i)
			for(int j = 0; j < Size; ++j)
				v[i][j].clear();
		n = read();
		int k, t, x, y;
		for(int i = 1; i <= n; ++i) {
			k = read();
			x = F(i);
			for(int j = 1; j <= k; ++j) {
				t = read();
				y = G(t);
				v[x][y].insert(mk(i, t));
				// cerr << x << " " << y << " " << i << " " << t << endl;
			}
		}
		// DEBUG__();
		bool fg = 0;
		for(int x1 = 0; x1 < Size && !fg; ++x1)
			for(int y1 = 0; y1 < Size && !fg; ++y1)
				if(!v[x1][y1].empty()) {
					for(int x2 = x1; x2 < Size && !fg; ++x2)
						for(int y2 = y1; y2 < Size; ++y2)
							if(check(x1, y1, x2, y2)) {
								fg = 1;
								break ;
							}
				}
		if(!fg)
			puts("-1");
	}			
	return 0;
}
