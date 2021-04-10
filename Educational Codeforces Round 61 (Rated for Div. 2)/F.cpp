#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n;
string s;
int f[N][N];

int dfs(int l, int r) {
	int & res = f[l][r];
	if(res != -1) return res;

	if(l > r) return res = 0;
	if(l == r) return res = 1;

	res = dfs(l, r - 1) + 1;
	for(int i = l; i < r; ++i)
		if(s[i] == s[r])
			res = min(res, dfs(l, i) + dfs(i + 1, r - 1));
	return res;
}

int main() {
	cin >> n;
	cin >> s;
	memset(f, -1, sizeof f);
	cout << dfs(0, n - 1);

	return 0;
}
