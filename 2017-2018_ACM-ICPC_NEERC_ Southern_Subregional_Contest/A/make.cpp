#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <time.h>
using namespace std;
int main() {
	freopen("A.in", "w", stdout);
	srand(time(0));
	int n = 100, m = 100, a = rand() % 20 + 1, d = rand() % 20 + 1;
	printf("%d %d %d %d\n", n, m, a, d);
	for(int i = 1; i <= m; ++i)
		printf("%d ", rand() % 10000 + 1);
	return 0;
}
