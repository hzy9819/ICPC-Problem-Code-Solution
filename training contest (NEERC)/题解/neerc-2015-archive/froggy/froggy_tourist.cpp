#include <cstdio>
#include <algorithm>

using namespace std;

#define FILENAME "froggy"

double dist[1234][1234];
int x[1234], y[1234];
double u[2][1234];
double d[1234], res[1234];

int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int w, n;
  scanf("%d %d", &w, &n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d", x + i, y + i);
  }
  for (int i = 0; i < n + 2; i++) {
    for (int j = 0; j < n + 2; j++) {
      if (i == j) {
        dist[i][j] = 0;
        continue;
      }
      if (i >= n && j >= n) {
        dist[i][j] = w;
        continue;
      }
      if (i >= n) {
        dist[i][j] = (i == n ? x[j] : w - x[j]);
        continue;
      }
      if (j >= n) {
        dist[i][j] = (j == n ? x[i] : w - x[i]);
        continue;
      }
      dist[i][j] = sqrt((x[i] - x[j]) * 1.0 * (x[i] - x[j]) + (y[i] - y[j]) * 1.0 * (y[i] - y[j]));
    }
  }
  double ans = 1e30, ax = -1, ay = -1;
  for (int start = n; start < n + 2; start++) {
    for (int i = 0; i < n + 2; i++) {
      d[i] = 1e30;
      res[i] = 1e30;
    }
    d[start] = 0;
    double mx = 0;
    for (int it = 0; it < n + 2; it++) {
      int best = -1;
      for (int i = 0; i < n + 2; i++) {
        if (res[i] > 1e29 && (best == -1 || d[i] < d[best])) {
          best = i;
        }
      }
      mx = max(mx, d[best]);
      res[best] = mx;
      for (int j = 0; j < n + 2; j++) {
        d[j] = min(d[j], dist[best][j]);
      }
    }
    for (int i = 0; i < n + 2; i++) {
      u[start - n][i] = res[i];
    }
  }
  for (int i = 0; i < n + 2; i++) {
    for (int j = 0; j < n + 2; j++) {
      double cur = max(dist[i][j] / 2, max(u[0][i], u[1][j]));
      if (cur < ans) {
        ans = cur;
        if (i == n && j == n + 1) {
          ax = 0.5 * w;
          ay = 0.0;
        }
        if (i < n && j < n) {
          ax = 0.5 * (x[i] + x[j]);
          ay = 0.5 * (y[i] + y[j]);
        }
        if (i == n && j < n) {
          ax = 0.5 * x[j];
          ay = y[j];
        }
        if (i < n && j == n + 1) {
          ax = 0.5 * (w + x[i]);
          ay = y[i];
        }
      }
    }
  }
  printf("%.17f %.17f\n", ax, ay);
  return 0;
}
