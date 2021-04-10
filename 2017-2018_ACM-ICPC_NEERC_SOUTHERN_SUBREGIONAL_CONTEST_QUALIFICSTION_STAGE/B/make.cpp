#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#define LL long long
using namespace std;
const int N = 200010;
int n, a[N];

int main() {
	freopen("B.in", "w", stdout);
	n = 1000;
	srand(time(0));
	for(int i = 1; i <= n; ++i) a[i] = rand();
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) printf("%d ", a[i]);
	return 0;
}
