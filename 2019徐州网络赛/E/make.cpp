#include <bits/stdc++.h>

using namespace std;
int n = 500000, m;
int main() {
	freopen("E.in", "w", stdout);
	srand(time(0));
	printf("%d %d\n", n, rand());
	for(int i = 0; i < n; ++i)
		printf("%d ", rand());
	return 0;
}
