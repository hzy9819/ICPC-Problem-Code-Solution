#include <cstdio>
#include <set>

using namespace std;

#define FILENAME "adjustment"

int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int n, q;
  scanf("%d %d", &n, &q);
  set <int> r;
  set <int> c;
  long long sr = n * 1LL * (n + 1) / 2;
  long long nr = n;
  long long sc = sr;
  long long nc = n;
  while (q--) {
    char ch = getchar();
    while (ch != 'R' && ch != 'C') {
      ch = getchar();
    }
    int id;
    scanf("%d", &id);
    if (ch == 'R') {
      if (r.find(id) != r.end()) {
        printf("0\n");
      } else {
        r.insert(id);
        printf("%lld\n", sc + id * nc);
        sr -= id;
        nr--;
      }
    } else {
      if (c.find(id) != c.end()) {
        printf("0\n");
      } else {
        c.insert(id);
        printf("%lld\n", sr + id * nr);
        sc -= id;
        nc--;
      }
    }
  }
  return 0;
}
