#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

vector <int> g[N];
int que[N];
int d[N];
int was[N];

int main() {
  freopen("distance.in", "r", stdin);
  freopen("distance.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    g[i].clear();
  }
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    g[i].push_back(j);
    g[j].push_back(i);
  }
  for (int i = 0; i < n - 3; i++) {
    int foo, bar;
    scanf("%d %d", &foo, &bar);
    foo--; bar--;
    g[foo].push_back(bar);
    g[bar].push_back(foo);
  }
  for (int i = 0; i < n; i++) {
    was[i] = -1;
  }
  int qs;
  scanf("%d", &qs);
  while (qs--) {
    int foo, bar;
    scanf("%d %d", &foo, &bar);
    foo--; bar--;
    if (foo == bar) {
      printf("%d\n", 0);
      continue;
    }
    int b = 0, e = 1;
    que[0] = foo;
    d[0] = 0;
    was[foo] = qs;
    while (b < e) {
      int x = que[b];
      int sz = g[x].size();
      for (int j = 0; j < sz; j++) {
        int y = g[x][j];
        if (was[y] != qs) {
          was[y] = qs;
          d[e] = d[b] + 1;
          que[e] = y;
          e++;
          if (que[e - 1] == bar) {
            break;
          }
        }
      }
      if (que[e - 1] == bar) {
        break;
      }
      b++;
    }
    printf("%d\n", d[e - 1]);
  }
  return 0;
}
