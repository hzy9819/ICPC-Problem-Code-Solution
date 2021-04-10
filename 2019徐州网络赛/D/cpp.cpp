#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define LL long long
#define db double
#define l first
#define r second
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int Q = 1010;
int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void GetNext(string & a, int * nxt) {
	int n = a.size();
	nxt[0] = 0;
	for(int i = 1, k = 0; i < n; ++i) {
		while(a[k] != a[i] && k != 0)
			k = nxt[k - 1];
		if(a[k] == a[i])
			k++;
		nxt[i] = k;
	}
}

bool KMP(string & a, string & b, int * nxt) {
	int n = a.size(), m = b.size();
	for(int i = 0, k = 0; i < n; ++i) {
		while(a[i] != b[k] && k != 0)
			k = nxt[k - 1];
		if(a[i] == b[k])
			k++;
		if(k == m)
			return 1;
	}
	return 0;
}

string T, S;
int nxt1[N], nxt2[N], q;

int main() {
	cin >> T;
	q = read();
	GetNext(T, nxt1);
	for(int i = 0; i < q; ++i) {
		cin >> S;
		if(S.size() < T.size()) {
			GetNext(S, nxt2);
			if(KMP(T, S, nxt2))
				printf("my child!");
			else
				printf("oh, child!");
		}
		else if(S.size() == T.size()) {
			if(S == T)
				printf("jntm!");
			else
				printf("friend!");
		}
		else {
			if(KMP(S, T, nxt1))
				printf("my teacher!");
			else
				printf("senior!");
		}
		if(i != q - 1)
			puts("");
	}
	return 0;
}
