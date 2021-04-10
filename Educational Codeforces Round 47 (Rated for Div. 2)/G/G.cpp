#include <bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int N = 100010;
const int Bits = 70;
char s[N], temp[Bits];
int n, m, can[N];
int cnt[Bits], f[Bits], bit[Bits], sum[Bits];

bool check() {
	sum[0] = 0;
	for(int i = 1; i <= 63; ++i) {
		sum[i] = sum[ i ^ (i & (-i)) ] + cnt[bit[i & (-i)]];
		if(sum[i] > f[63] - f[63 - i]) return false;
	}
	return true;
}

int read() {
	int f = 0, w = 0; char c = getchar();
	while((c != '-') && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

int main() {
	Hzy("G");
	scanf("%s", s + 1); n = strlen(s + 1);
	for(int i = 1; i <= n; ++i) {
		can[i] = 63;
		cnt[s[i] - 'a']++;
	}
	for(int i = 0; i < 6; ++i)
		bit[1 << i] = i;
	m = read();
	for(int i = 1, len, P; i <= m; ++i) {
		P = read();
		can[P] = 0;
		scanf("%s", temp + 1);
		len = strlen(temp + 1);
		for(int j = 1; j <= len; ++j)
			can[P] |= 1 << (temp[j] - 'a');
	}
	for(int i = 1; i <= n; ++i) f[can[i]]++;
	for(int i = 63; i >= 0; --i)
		for(int j = (i - 1) & i; ; j = (j - 1) & i) {
			f[i] += f[j];
			if(!j) break;
		}
	if(!check()) {
		puts("Impossible");
		return 0;
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = can[i]; j <= 63; j = ((j + 1) | can[i])) f[j]--;
		for(int j = 0; j < 6; ++j)
			if(can[i] & (1 << j)) {
				if(cnt[j] < 1) continue;
				cnt[j]--;
				if(check()) {
					putchar(j + 'a');
					break;
				}
				cnt[j]++;
			}
	}
	return 0;
}
