#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> dll;
int n;
char a[30], b[30];
int la, lb;
set<dll> s;
int ans;
int flag, un, on, kn;
void Sol() {
	if(flag == -1) {
		for(int k = 0; k < un; k++) b[lb++] = 'u';
		for(int k = 0; k < (on >> 1); k++) b[lb++] = 'u';
		if(on & 1) b[lb++] = 'o';
	}
	else if(flag) {
		for(int k = 0; k < kn; k++) b[lb++] = 'k';
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%s", a);
		la = strlen(a);
		lb = 0;
		flag = 0, un = 0, on = 0, kn = 0;
		for(int j = 0; j < la; j++) {
			if(a[j] == 'k') {
				if(flag == 1) kn++;
				else {
					Sol();
					flag = 1;
					kn = 1;
				}
			}
			else if(a[j] == 'h') {
				if(flag == 1) flag = 0;
				Sol();
				b[lb++] = 'h';
				flag = 0;
			}
			else if(a[j] == 'u') {
				if(flag == -1) un++;
				else {
					Sol();
					flag = -1;
					un = 1;
					on = 0;
				}
			}
			else if(a[j] == 'o') {
				if(flag == -1) on++;
				else {
					Sol();
					flag = -1;
					un = 0;
					on = 1;
				}
			}
			else {
				Sol();
				b[lb++] = a[j];
				flag = 0;
			}
		}
		Sol();
		ll p = 0, q = 0;
		ll t = 1;
		for(int j = 0; j < min(lb, 10); j++) {
			q += (b[j] - 'a' + 1) * t;
			t *= 27;
		}
		t = 1;
		for(int j = 10; j < lb; j++) {
			p += (b[j] - 'a' + 1) * t;
			t *= 27;
		}
		dll np(p, q);
		if(s.find(np) == s.end()) {
			s.insert(np);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}

