#include <cstdio>
#include <vector>

using namespace std;

int n, k;

int main(){ 
  freopen("easy.in", "r", stdin);
  freopen("easy.out", "w", stdout);
  scanf("%d%d",&n,&k);
  vector<vector<int>> v(n);
  for (int i = 0; i < n; i++) {
    int s;
    scanf("%d",&s);
    v[i].resize(s);
    for (int& x : v[i]) {
      scanf("%d",&x);
    }
  }

  int tot = 0;
  int it = 0;
  while (k) {
    bool any = false;
    for (int i = 0; i < n && k; i++) {
      int cur;
      if (it < v[i].size()) {
        cur = v[i][it];
        any = true;
      } else {
        cur = 50;
      }
      if (cur >= tot) {
        tot += cur;
        k--;
      }
    }
    if (!any) break;
    it++;
  }
  tot += 50 * k;
  printf("%d\n", tot);
}
