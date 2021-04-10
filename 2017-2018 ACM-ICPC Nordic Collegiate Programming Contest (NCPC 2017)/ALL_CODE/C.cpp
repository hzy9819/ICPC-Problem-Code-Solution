#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int n;
int ang[N][3];
int realid[N];
struct Ang {
	int x, id; Ang *l, *r;
	Ang(){}
	Ang(int x, int id): x(x), id(id){}
	bool operator < (const Ang &rhs) const {
		return x < rhs.x;
	}
}a[3][N], b[N];
int an[3][360];
struct Data {
	int r, g, b, id;
	bool operator < (const Data &rhs) const {
		return id < rhs.id;
	}
}data[N];
struct Node {
	int x, id;
	Node(){}
	Node(int x, int id): x(x), id(id){}
	bool operator < (const Node &rhs) const {
		return x == rhs.x ? id < rhs.id : x > rhs.x;
	}
};
int val[3][N];
int sum[N];
priority_queue<Node> q;
int mt[N], num;

void maintain(Ang *u, int d) {
	mt[++num] = u->id;
	val[d][u->id] = u->r->x - u->l->x;
	if(u->l->x > u->x) val[d][u->id] += 360;
	else if(u->x > u->r->x) val[d][u->id] += 360;
}

void Init() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d%d%d", &data[i].r, &data[i].g, &data[i].b, &data[i].id);
	}
	sort(data + 1, data + n + 1);
	for(int i = 1; i <= n; i++) {
		realid[i] = data[i].id;
		an[0][ang[i][0] = data[i].r] ++;
		an[1][ang[i][1] = data[i].g] ++;
		an[2][ang[i][2] = data[i].b] ++;
		a[0][i] = Ang(data[i].r, i);
		a[1][i] = Ang(data[i].g, i);
		a[2][i] = Ang(data[i].b, i);
	}
	for(int i = 0; i < 3; i++) {
		memcpy(b, a[i], sizeof b);
		sort(b + 1, b + n + 1);
		for(int j = 1; j <= n; j++) {
			a[i][b[j].id].l = &a[i][b[j - 1].id];
			a[i][b[j].id].r = &a[i][b[j + 1].id];
		}
		a[i][b[1].id].l = &a[i][b[n].id];
		a[i][b[n].id].r = &a[i][b[1].id];
		for(int j = 1; j <= n; j++) {
			if(an[i][a[i][j].x] > 1) continue;
			maintain(&a[i][j], i);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < 3; j++) sum[i] += val[j][i];
		q.push(Node(sum[i], i));
	}
}

void Modify(int id, int d) {
	if(--an[d][a[d][id].x] > 1) {
		a[d][id].l->r = a[d][id].r;
		a[d][id].r->l = a[d][id].l;
	}
	else if(an[d][a[d][id].x] == 1) {
		Ang *v;
		if(a[d][id].l->x == a[d][id].x) {
			v = a[d][id].l;
			v->r = a[d][id].r;
			v->r->l = v;
			if(v->l == &a[d][id]) v->l = v;
		}
		else {
			v = a[d][id].r;
			v->l = a[d][id].l;
			v->l->r = v;
			if(v->r == &a[d][id]) v->r = v;
		}
		maintain(v, d);
	}
	else {
		Ang *l = a[d][id].l;
		Ang *r = a[d][id].r;
		l->r = r;
		r->l = l;
		if(l->x != l->l->x) maintain(l, d);
		if(r->x != r->r->x) maintain(r, d);
	}
}
bool vis[N];
int main() {
	Init();
	while(!q.empty()) {
		Node u = q.top(); q.pop();
		if(vis[u.id] || u.x != sum[u.id]) continue;
		printf("%d\n", realid[u.id]);
		if(!--n) break;
		vis[u.id] = 1;
		num = 0;
		for(int i = 0; i < 3; i++) Modify(u.id, i);
		for(int i = 1; i <= num; i++) {
			sum[mt[i]] = 0;
			for(int j = 0; j < 3; j++) sum[mt[i]] += val[j][mt[i]];
			q.push(Node(sum[mt[i]], mt[i]));
		}
	}
	return 0;
}

