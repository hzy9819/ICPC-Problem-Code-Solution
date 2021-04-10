#include <cstdio>
#include <algorithm>
int x1, y1, x2, y2;
int main() {
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	int t = 0;
	if(x1 == x2) t += 2;
	else t ++;
	if(y1 == y2) t += 2;
	else t ++;
	printf("%d", (abs(x1 - x2) + abs(y1 - y2) + t) << 1);
	return 0;
}

