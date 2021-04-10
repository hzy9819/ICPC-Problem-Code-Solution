#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int INF = 1 << 30;
const LL inf = 1LL << 60;

int read() {
	int w(0), f(0); char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
LL x = 1, y = 2;
string s;
int main() {
	while(cin >> s) {
		if(s == "end" || s == "mistake") break;
		if(s == "start") 
			x = 1, y = 2;
		else if(s == "y") 
			x *= 2, y *= 2;
		else if(s == "x") {
			if(x == 1 && y == 2) {
				puts("? 2 1");
				fflush(stdout);
				cin >> s;
				if(s == "x") puts("! 1");
				else puts("! 2");
				fflush(stdout);
				continue;
			}
			else {
				int l = 0, r = y - x, mid, ans = r;
				for(mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1) {
					cout << "? " << x + mid << " " << y << endl;
					//printf("? %d %d\n", x + mid, y);
					fflush(stdout);
					cin >> s;
					if(s == "x") l = mid + 1;
					else r = mid - 1, ans = mid;
				}
				cout << "! " << x + ans << endl;
				//printf("! %d\n", x + ans);
				fflush(stdout);
				continue;
			}
		}
		cout << "? " << x << " " << y << endl;
		//printf("? %d %d\n", x, y);
		fflush(stdout);
	}
	return 0;
}
