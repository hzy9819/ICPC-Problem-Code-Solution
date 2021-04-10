#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 105;
int n, k, m, a;
struct Node {
	int num, last, id;
	bool operator < (const Node &rhs) const {
		return num == rhs.num ? last < rhs.last : num > rhs.num;
	}
}p[N];
bool yes(int x) {
	if(!p[x].num) return 0;
	if(x > k) return 0;
	if(n == k) return 1;
	int sum = 0;
	for(int i = x + 1; i <= k + 1; i++) {
		sum += p[x].num + 1 - p[i].num;
	}
	return sum > m - a;
}
bool no(int x) {
	int num = p[x].num + m - a;
	if(!num) return 1;
	if(x <= k) return 0;
	for(int i = 1; i <= k; i++) {
		if(num > p[i].num) return 0;
	}
	return 1;
}
int rk[N];
int main() {
	scanf("%d%d%d%d", &n, &k, &m, &a);
	for(int i = 1; i <= n; i++) p[i].id = i;
	for(int i = 1, x; i <= a; i++) {
		scanf("%d", &x);
		p[x].num++;
		p[x].last = i;
	}
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; i++) rk[p[i].id] = i;
	for(int i = 1; i <= n; i++) {
		if(yes(rk[i])) printf("1 ");
		else if(no(rk[i])) printf("3 ");
		else printf("2 ");
	}
	return 0;
}

