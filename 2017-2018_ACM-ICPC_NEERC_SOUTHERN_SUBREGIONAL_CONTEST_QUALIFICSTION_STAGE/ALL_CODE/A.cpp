#include <cstdio>
using namespace std;
const int N = 105;
int n;
int l[N], r[N];
int head[N], tail[N];
int nh, nt;
int fa[N];
int find(int x) {return x == fa[x] ? x : (fa[x] = find(fa[x]));}
struct Node {
	int head, tail;
	Node(){}
	Node(int h, int t):head(h), tail(t){}
}p[N];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", l + i, r + i);
		if(l[i]) fa[i] = l[i];
		else head[++nh] = i;
		if(r[i]) fa[r[i]] = i;
		else tail[++nt] = i;
	}
	for(int i = 1; i <= nh; i++) {
		p[i] = Node(find(tail[i]), tail[i]);
	}
	for(int i = 2; i <= nt; i++) {
		r[p[1].tail] = p[i].head;
		l[p[i].head] = p[1].tail;
		p[1].tail = p[i].tail;
	}
//	for(int i = 1; i < nh; i++) {
//		int fi = find(head[i]);
//		for(int j = 1; j <= nt; j++) {
//			int fj = find(tail[j]);
//			if(fi != fj) {
//				r[tail[j]] = head[i];
//				l[head[i]] = tail[j];
//				fa[fi] = fj;
//				break;
//			}
//		}
//	}
	for(int i = 1; i <= n; i++) printf("%d %d\n", l[i], r[i]);
	return 0;
}

