#include <bits/stdc++.h>
using namespace std;
bool fg[1001];
int main() {
	freopen("A.in", "r", stdin), freopen("std.out", "w", stdout);
	int n, m;
	cin >> n >> m;
	int a[101], b[101];
	for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];

	for(int i = 0; i < n; ++i)
		for(int j = a[i]; j < b[i]; ++j) fg[j] = 1;

	for(int i = 0; i < m; ++i) {
		if(!fg[i]) {
			cout << "NO";
			return 0;
		}
	}
	cout << "YES";
	return 0;
}
