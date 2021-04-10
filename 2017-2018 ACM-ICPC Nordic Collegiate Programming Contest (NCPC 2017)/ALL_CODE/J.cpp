#include <cstdio>
#include <algorithm>
using namespace std;
int a, b;
int main() {
	scanf("%d%d", &a, &b);
	if(a == b) {
		if(a) printf("Even %d\n", a << 1);
		else printf("Not a moose\n");
	}
	else printf("Odd %d\n", max(a, b) << 1);
	return 0;
}

