#include <cstdio>
#include <vector>

using namespace std;

#define FILENAME "landscape"

const long long inf = (long long)2e18;

const int N = 1234567;

int h[N];
vector <int> ev[N];
long long ans[N];
long long sum[N];

int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int n;
  long long m;
  scanf("%d %lld", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", h + i);
  }
  int low = 0;
  for (int i = 0; i < n; i++) {
    low = max(low, h[i]);
  }
  int high = (int)1.01e9;
  while (low < high) {
    int mid = (low + high + 1) >> 1;
    for (int i = 0; i < n; i++) {
      ans[i] = 0;
    }
    for (int rot = 0; rot < 2; rot++) {
      sum[0] = h[0];
      for (int i = 1; i < n; i++) {
        sum[i] = sum[i - 1] + h[i];
      }
      for (int i = 0; i < n; i++) {
        ev[i].clear();
      }
      for (int i = 0; i < n; i++) {
        int j = i + mid - h[i];
        if (j < n) {
          ev[j].push_back(i);
        }
      }
      int mx = -1;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int) ev[i].size(); j++) {
          mx = max(mx, ev[i][j]);
        }
        if (mx >= 0) {
          int from = mid - 1;
          int to = mid - (i - mx) + 1;
          ans[i] += (to + from) * 1LL * (from - to + 1) / 2;
          ans[i] -= (sum[i - 1] - sum[mx]);
        } else {
          ans[i] += inf;
        }
      }
      for (int i = 0; i < n - i - 1; i++) {
        swap(h[i], h[n - i - 1]);
        swap(ans[i], ans[n - i - 1]);
      }
    }
    bool found = false;
    for (int i = 0; i < n; i++) {
      ans[i] += mid - h[i];
      if (ans[i] <= m) {
        found = true;
        break;
      }
    }
    if (found) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }
  printf("%d\n", low);
  return 0;
}
