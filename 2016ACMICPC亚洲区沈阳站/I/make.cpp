#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;
int n = 100000, p = 1000000;

int main() {
	freopen("I.in", "w", stdout);
	srand(time(0));
	puts("1");
	printf("%d %d\n", n, p);
	for(int i = 2; i <= n; ++i)
		printf("%d %d %d\n", rand() % (i - 1) + 1, i, rand() % 100 + 1);
	return 0;
}
