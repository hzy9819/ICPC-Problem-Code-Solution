#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 110;
struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
	int other(int x) { return x ^ u ^ v ; }
}e[N];
vector <int> v[5];
int n, ans, Min;
int c[N], col = 1, sum[5], acu[5];
bool vis[N];
queue <int> Q;

int Sol(int t, int col) {
	int ans = 0;
	c[t] = col;
	for(size_t i = 0; i < v[t].size(); ++i)
		if(!vis[v[t][i]]) {
			int tmp = v[t][i];
			vis[tmp] = 1;
			acu[e[tmp].u]++, acu[e[tmp].v]++;
			ans += Sol(e[tmp].other(t), col) + e[tmp].w;
			if((v[e[tmp].u].size() & 1) && (v[e[tmp].v].size() & 1) && (e[tmp].u != e[tmp].v))
				//Min = min(Min, e[tmp].w);
				Q.push(tmp);
		}
	return ans;
}
int main() {
	Hzy("E");
	scanf("%d", &n);
	int _u, _v, _w;
	for(int i = 1; i <= n; ++i) {
		scanf("%d %d %d", &_u, &_w, &_v) ;
		e[i] = Edge(_u, _v, _w);
		if(_u == _v) {
			sum[_u] += _w;
			n--, i--;
			continue;
		}
		v[_u].push_back(i);
		v[_v].push_back(i);
	}
	for(int i = 1; i <= 4; ++i) ans = max(ans, sum[i]);
	for(int i = 1; i <= 4; ++i)
		if(!c[i]) {
			Min = (1 << 30);
			while(!Q.empty()) Q.pop();
			for(int j = 1; j <= 4; ++j)
				acu[j] = 0;
			int res = Sol(i, col++), tmp = 0;
			for(int j = 1; j <= 4; ++j)
				if(c[j] == col - 1 && (v[j].size() & 1))
					tmp++;
			if(tmp == 4) {
				while(!Q.empty()) {
					int t = Q.front(), s = 0;
					Q.pop();
					acu[e[t].u]--, acu[e[t].v]--;
					for(int j = 1; j <= 4; ++j)
						if(acu[j]) s += sum[j];
					acu[e[t].u]++, acu[e[t].v]++;
					s -= e[t].w;
					ans = max(ans, res + s);
				}
			}
			else {
				int s = 0;
				for(int j = 1; j <= 4; ++j)
					if(acu[j]) s += sum[j];
				ans = max(ans, res + s);
			}
			//ans = max(ans, res);
		}
	cout << ans << endl;
	return 0;
}
