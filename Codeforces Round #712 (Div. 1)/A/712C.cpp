
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		stack<char> sta;
		sta.push('#');
		if (n % 2 == 1) cout << "NO" << '\n';
		else {
			for (int i = 0; !sta.empty() and i < n; i++) {
				if ((i % 2 + (s[i] - '0')) % 2 == 1) sta.push('(');
				else sta.pop();
			}
			if (sta.empty() or sta.top() != '#') cout << "NO" << '\n';
			else {
				cout << "YES" << '\n';
				for (int i = 0; i < n; i++) 
					if (i % 2 == 0) cout << '(';
					else cout << ')';
				cout << '\n';
				for (int i = 0; i < n; i++) 
					if ((i % 2 + (s[i] - '0')) % 2 == 1) cout << '(';
					else cout << ')';
				cout << '\n';
			}
		}
	}
	return 0;
}

