#include <bits/stdc++.h>
#define X first
#define Y second
#define maxn 200005
#define db double
#define LL long long
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
struct Pt {
    int x, id;
    bool operator < (const Pt &a) const {
        return x < a.x;
    }
};
 
const int INF = 0x3f3f3f3f;
 
int ans[maxn], dp[maxn], pre[maxn];
int n, mx, mi;
Pt arr[maxn];
 
/*
dp[i] = arr[i] + min(dp[j - 1] - arr[j]))
*/
/*
 1 2 5 12 13 15
*/
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &arr[i].x);
        arr[i].id = i;
    }
    deque< pair<int, int> > dq;
    sort(arr + 1, arr + n + 1);
    for(int i = 1; i <= min(n, 5); i++) {
        if(i < 3)
            dp[i] = INF;
        else
            dp[i] = arr[i].x - arr[1].x, pre[i] = 1;
    }
    dq.push_back({4, dp[3] - arr[4].x});
    for(int i = 6; i <= n; i++) {
 
        dp[i] = arr[i].x + dq.front().Y;
        pre[i] = dq.front().X;
 
 
        while(dq.size() && dq.back().Y > dp[i - 2] - arr[i - 1].x) dq.pop_back();
        dq.push_back({i - 1, dp[i - 2] - arr[i - 1].x});
 
    }
    int tot = 0;
 
    for(int i = n; i > 0; ) {
 
        int j = i; tot++;
        for(; j >= pre[i]; j--) {
            ans[arr[j].id] = tot;
        }
        i = j;
 
    }
 
    printf("%d %d\n", dp[n], tot);
    for(int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
