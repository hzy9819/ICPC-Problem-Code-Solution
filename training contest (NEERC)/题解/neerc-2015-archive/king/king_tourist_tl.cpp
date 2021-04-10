#include <vector>
#include <algorithm>
#include <cstdio>

#pragma comment(linker, "/STACK:36777216")
 
using namespace std;
 
#define FILENAME "king"
 
#define NO "There is no route, Karl!"
 
const int N = 1234567;
 
vector <int> go[N], gi[N];
int a[N], b[N];
bool was[N];
int n;
 
void dfs(int v, int w) {
  if (w == n) {
    for (int i = 0; i < n; i++) {
      printf("%d ", a[i] + 1);
    }
    printf("1\n");
    exit(0);
  }
  if (0 < w && w < n && v == 0) return;
  for (int j = 0; j < (int) go[v].size(); j++) {
    int u = go[v][j];
    if (!was[u]) {
      was[u] = true;
      a[w + 1] = u;
      dfs(u, w + 1);
      was[u] = false;
    }
  }
}
 
int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int m;
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) {
    go[i].clear();
    gi[i].clear();
  }
  for (int i = 0; i < m; i++) {
    scanf("%d %d", a + i, b + i);
    a[i]--; b[i]--;
    go[a[i]].push_back(b[i]);
    gi[b[i]].push_back(a[i]);
  }

  for (int i = 0; i < n; i++) {
    if (go[i].empty() || gi[i].empty()) {
      puts(NO);
      return 0;
    }
  }

  for (int i = 0; i < n; i++) {
    was[i] = false;
  }
  a[0] = 0;
  dfs(0, 0);
  puts(NO);
  return 0;
}
