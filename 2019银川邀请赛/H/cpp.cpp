#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int t, n;

struct hp{
	int blood, attack, turn;
	bool operator < (const hp & x) const {
		return (attack * x.turn >= x.attack * turn);
	}
}monster[100010];

int main() {
	int cnt = 0;
	scanf("%d",&t);
	while (t--) {
		cnt+=1;
		scanf("%d",&n);
		for (int i = 1;i <= n;++i) {
			scanf("%d%d", &monster[i].blood, &monster[i].attack);
			monster[i].turn = (int)(ceil((sqrt(monster[i].blood * 8 + 1) - 1) / 2)) - 1;
			while (monster[i].turn * (monster[i].turn + 1) / 2 < monster[i].blood) {
				monster[i].turn += 1;		
			}
		}
		long long harm = 0;
		int turn_tot = 0;
		sort(monster + 1, monster + n + 1);
		for (int i = 1;i <= n;++i) {
			turn_tot += monster[i].turn;
			harm = harm + 1LL * turn_tot * monster[i].attack;
		}
		printf("Case #%d: %lld\n", cnt, harm);
	}
}
