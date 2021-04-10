#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 200010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}
char s[N];
int st1, st2;
LL xmin, xmax, ymin, ymax, w, h, x, y;
LL ans;
bool fg1, fg2;
int main() {
	Hzy("C");
	int T = read();
	while(T--) {
		scanf("%s", s);
		int n = strlen(s);
		xmin = xmax = ymin = ymax = 0;
		x = y = 0;
		fg1 = fg2 = 0;
		st1 = st2 = 0;
		for(int i = 0; i < n; ++i)
			if(s[i] == 'W') {
				y++;
				if(y == ymax) 
					fg2 = (st2 == -1 || st2 == 0 || fg2);				
				else if(y > ymax) {
					ymax = y;
					fg2 = 0;
					st2 = 1;
				}
			}
			else if(s[i] == 'S') {
				y--;
				if(y == ymin) 
					fg2 = (st2 == 1 || st2 == 0 || fg2);
				else if(y < ymin) {
					ymin = y;
					fg2 = 0;
					st2 = -1;
				}
			}
			else if(s[i] == 'A') {
				x--;
				if(x == xmin) 
					fg1 = (st1 == 1 || st1 == 0 || fg1);
				else if(x < xmin) {
					xmin = x;
					fg1 = 0;
					st1 = -1;
				}
			}
			else if(s[i] == 'D') {
				x++;
				if(x == xmax) 
					fg1 = (st1 == -1 || st1 == 0 || fg1);
				else if(x > xmax) {
					xmax = x;
					fg1 = 0;
					st1 = 1;
				}
			}
		w = xmax - xmin + 1;
		h = ymax - ymin + 1;

		if(w <= 2) fg1 = 1;
		if(h <= 2) fg2 = 1;
		
		if(fg1 && fg2)
			ans = w * h;
		else if(fg1)
			ans = w * max(h - 1, 1LL);
		else if(fg2)
			ans = max(w - 1, 1LL) * h;
		else 
			ans = w * h - max(w, h);
			
		
				
		cout << ans << endl;
	}
				
	return 0;
}
