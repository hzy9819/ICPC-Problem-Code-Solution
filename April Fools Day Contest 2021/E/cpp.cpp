#include <bits/stdc++.h>
#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

char s[10][10];
int n, m;

bool judge(pair<int, int> a, pair<int, int> b, pair<int, int> pos) {
	if(b.l < pos.l || b.r < pos.r || b == pos)
		return false;
	if(a == pos)
		return true;
	int dis1 = a.l - pos.l + a.r - pos.r;
	int dis2 = b.l - pos.l + b.r - pos.r;
	if(dis1 < dis2)
		return false;
	if(dis2 < dis1)
		return true;
	return a.r < b.r;
}

int main() {
	n = read(), m = read();
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	pair<int, int> pos = mk(0, 0);
	int ans = 0;
	if(s[0][0] == '*')
		ans++;
	do {
		pair<int, int> temp = pos;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(s[i][j] == '*' && judge(temp, mk(i, j), pos))
					temp = mk(i, j);
		if(temp == pos)
			break;
		else
			ans++;
		pos = temp;
	}while(1);
	cout << ans << endl;
	
	return 0;
}
