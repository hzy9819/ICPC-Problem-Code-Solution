#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
int n;
char a[N];
int pos[N], m;
bool judge(int x) {
	int j = 1;
	for(int i = 1; i <= m; i++) {
		for(; j <= n && a[j] != '*'; j++) ;
		if(j > n) return 1;
		if(j < pos[i]) {
			if(pos[i] - j > x) return 0;
			j = max(x - ((pos[i] - j) << 1), (x - (pos[i] - j)) >> 1) + pos[i] + 1;
		}
		else j = max(pos[i] + x + 1, j);
	}
	for(; j <= n && a[j] != '*'; j++) ;
	return n < j;
}
int main() {
	scanf("%d%s", &n, a + 1);
	for(int i = 1; i <= n; i++) if(a[i] == 'P') pos[++m] = i;
	int l = 1, r = n << 1, mid, ans;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(judge(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}

