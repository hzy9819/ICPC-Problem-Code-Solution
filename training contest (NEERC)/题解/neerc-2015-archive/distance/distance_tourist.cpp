#include <cstdio>
#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 200010;

vector <int> g[N];
int pos[N];
int que[N];

struct Poly {
  vector <int> v;                 // sorted list of vertices
  vector < pair <int, int> > e;   // list of diagonals
  int fst, snd;                   // ends of separating diagonal (fst < snd)
  vector <int> d_fst, d_snd;      // distances from fst and snd to all vertices
  Poly *in, *out;                 // children polygons

  void bfs(int start, vector <int> &d) {
    int cnt = v.size();
    for (int i = 0; i < cnt; i++) {
      g[v[i]].clear();
    }
    for (int i = 0; i < cnt - 3; i++) {
      int x = e[i].first;
      int y = e[i].second;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    for (int i = 0; i < cnt; i++) {
      int j = (i + 1) % cnt;
      g[v[i]].push_back(v[j]);
      g[v[j]].push_back(v[i]);
    }
    d.resize(cnt);
    for (int i = 0; i < cnt; i++) {
      d[i] = -1;
    }
    int b = 0, e = 1;
    que[0] = start;
    d[pos[start]] = 0;
    while (b < e) {
      int x = que[b];
      int sz = g[x].size();
      for (int j = 0; j < sz; j++) {
        int y = g[x][j];
        if (d[pos[y]] == -1) {
          d[pos[y]] = d[pos[x]] + 1;
          que[e] = y;
          e++;
        }
      }
      b++;
    }
  }

  void process() {
    if (v.size() <= 3) {
      return;
    }
    int cnt = v.size();
    for (int i = 0; i < cnt; i++) {
      pos[v[i]] = i;
    }
    int best = -1;
    fst = snd = -1;
    for (int i = 0; i < cnt - 3; i++) {
      int x = e[i].first;
      int y = e[i].second;
      int diff = abs(pos[x] - pos[y]);
      diff = min(diff, cnt - diff);
      if (diff > best) {
        best = diff;
        fst = min(x, y);
        snd = max(x, y);
      }
    }
    bfs(fst, d_fst);
    bfs(snd, d_snd);
    in = new Poly();
    out = new Poly();
    for (int i = pos[fst]; i <= pos[snd]; i++) {
      in->v.push_back(v[i]);
    }
    for (int i = 0; i <= pos[fst]; i++) {
      out->v.push_back(v[i]);
    }
    for (int i = pos[snd]; i < cnt; i++) {
      out->v.push_back(v[i]);
    }
    for (int i = 0; i < cnt - 3; i++) {
      int x = e[i].first;
      int y = e[i].second;
      if ((fst < x && x < snd) || (fst < y && y < snd)) {
        in->e.push_back(e[i]);
      }
      if ((fst > x || x > snd) || (fst > y || y > snd)) {
        out->e.push_back(e[i]);
      }
    }
    in->process();
    out->process();
  }

  int distance(int x, int y) {
    if (x == y) {
      return 0;
    }
    if (v.size() <= 3) {
      return 1;
    }
    if ((fst < x && x < snd) && (fst < y && y < snd)) {
      return in->distance(x, y);
    }
    if ((fst > x || x > snd) && (fst > y || y > snd)) {
      return out->distance(x, y);
    }
    int px = lower_bound(v.begin(), v.end(), x) - v.begin();
    int py = lower_bound(v.begin(), v.end(), y) - v.begin();
    int res = min(d_fst[px] + d_fst[py],
                  d_snd[px] + d_snd[py]);
    return res;
  }
};

int main() {
  freopen("distance.in", "r", stdin);
  freopen("distance.out", "w", stdout);
  int n;
  scanf("%d", &n);
  Poly *root = new Poly();
  root->v.resize(n);
  for (int i = 0; i < n; i++) {
    root->v[i] = i;
  }
  for (int i = 0; i < n - 3; i++) {
    int foo, bar;
    scanf("%d %d", &foo, &bar);
    foo--; bar--;
    root->e.push_back(make_pair(foo, bar));
  }
  root->process();
  int qs;
  scanf("%d", &qs);
  while (qs--) {
    int foo, bar;
    scanf("%d %d", &foo, &bar);
    foo--; bar--;
    int res = root->distance(foo, bar);
    printf("%d\n", res);
  }
  cerr << clock() << " ms" << endl;
  return 0;
}
