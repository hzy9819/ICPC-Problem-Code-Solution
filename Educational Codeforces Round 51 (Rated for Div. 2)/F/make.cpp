#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#define LL long long
using namespace std;
int n = 100000, m = 100020, q = 100000;
int main() {
	freopen("F.in", "w", stdout);
	srand(time(0));
	cout << n << " " << m << endl;
	for(int i = 1; i < n; ++i)
		cout << i << " " << i + 1 << " " << rand() << endl;
	for(int i = n; i <= m; ++i)
		cout << (i - n + 1) * 2 << " " << (i - n + 1) * 2 + 1 << " " << rand() << endl;
	cout << q << endl;
	for(int i = 1; i <= q; ++i)
		cout << i << " " << (i + 1) % n + 1 << endl;
	return 0;
}
