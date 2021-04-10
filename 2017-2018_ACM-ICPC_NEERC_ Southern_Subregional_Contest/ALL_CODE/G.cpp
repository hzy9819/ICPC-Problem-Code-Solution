#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 3e5 + 5;
struct Edge {
	int v; Edge *next;
	bool d; int id;
	Edge(){}
	Edge(int v, Edge *next, bool d, int id): v(v), next(next), d(d), id(id){}
}pool[N << 1], *pis = pool, *fst[N];
void Add(int u, int v, bool d, int id) {
	*pis = Edge(v, fst[u], d, id); fst[u] = pis++;
}
bool vis[N];
int dir[N];
int ans;
bool d;
void DFS(int u) {
	vis[u] = 1;
	ans++;
	for(Edge *i = fst[u]; i; i = i->next) {
		if(vis[i -> v]) continue;
		if(i->d) {
			if(d) dir[abs(i->id)] = i->id > 0 ? 1 : -1;
			else {
				dir[abs(i->id)] = i->id > 0 ? -1 : 1;
				continue;
			}
		}
		DFS(i->v);
	}
}
int n, m, s;
int k;
int main() {
	scanf("%d%d%d", &n, &m, &s);
	for(int i = 0, u, v, d; i < m; i++) {
		scanf("%d%d%d", &d, &u, &v);
		if(d == 1) Add(u, v, 0, 0);
		else {
			k++;
			Add(u, v, 1, k);
			Add(v, u, 1, -k);
		}
	}
	d = 1;
	DFS(s);
	printf("%d\n", ans);
	for(int i = 1; i <= k; i++) printf("%c", dir[i] == 1 ? '+' : '-');
	printf("\n");
	d = ans = 0;
	memset(vis, 0, sizeof vis);
	DFS(s);
	printf("%d\n" ,ans);
	for(int i = 1; i <= k; i++) printf("%c", dir[i] == 1 ? '+' : '-');
	return 0;
}

