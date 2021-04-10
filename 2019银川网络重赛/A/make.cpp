#include <bits/stdc++.h>
using namespace std;
int n = 1000, q = 1000;
int main() {
	freopen("A.in", "w", stdout);
	srand(time(0));
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i)
		printf("%d ", rand());
	puts("");
	printf("%d\n", q);
	for(int i = 1; i <= q; ++i) {
		int type = rand() % 4 + 1, l = rand() % n + 1, r = rand() % n + 1;
		if(l > r) swap(l, r);
		if(type <= 1)
			printf("%d %d %d\n", type, l, r);
		else
			printf("%d %d %d %d\n", type, l, r, rand());
	}
	return 0;
}
		
