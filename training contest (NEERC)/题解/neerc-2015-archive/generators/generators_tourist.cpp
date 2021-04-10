#include <cstdio>
#include <vector>

using namespace std;

#define FILENAME "generators"

const int inf = (int)1e9;
const int N = 1234567;

bool was[N];
int take[N], take2[N];

int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int n, k;
  scanf("%d %d", &n, &k);
  int ans = 0;
  int best = inf, pos = -1;
  for (int i = 0; i < n; i++) {
    int x, a, b, c;
    scanf("%d %d %d %d", &x, &a, &b, &c);
    for (int j = 0; j < c; j++) {
      was[j] = false;
    }
    vector <int> z;
    while (!was[x]) {
      z.push_back(x);
      was[x] = true;
      x = (x * a + b) % c;
    }
    int mx = -1, mp = -1;
    for (int i = 0; i < (int) z.size(); i++) {
      if (z[i] > mx) {
        mx = z[i];
        mp = i;
      }
    }
    int mx2 = -1, mp2 = -1;
    for (int i = 0; i < (int) z.size(); i++) {
      if (z[i] % k != mx % k && z[i] > mx2) {
        mx2 = z[i];
        mp2 = i;
      }
    }
    take[i] = mp;
    take2[i] = mp2;
    ans += mx;
     int diff = mx - mx2;
    if (mp2 != -1 && diff < best) {
      best = diff;
      pos = i;
    }
  }
  if (ans % k == 0 && best == inf) {
    printf("%d\n", -1);
    return 0;
  }
  if (ans % k == 0) {
    ans -= best;
    take[pos] = take2[pos];
  }
  printf("%d\n", ans);
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      putchar(' ');
    }
    printf("%d", take[i]);
  }
  printf("\n");
  return 0;
}
