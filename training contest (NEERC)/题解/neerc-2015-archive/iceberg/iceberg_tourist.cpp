#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define FILENAME "iceberg"

struct Order {
  int id, t, p, v, tv;
  int cv, pr;
};

struct cmp {
  bool operator() (const Order& lhs, const Order& rhs) const {
    if (lhs.p != rhs.p) {
      return lhs.p < rhs.p;
    }
    return lhs.pr < rhs.pr;
  }
};

struct Trade {
  int buy_id, sell_id, p, v;

  bool operator <(const Trade &other) const {
    if (buy_id != other.buy_id) {
      return buy_id < other.buy_id;
    }
    if (sell_id != other.sell_id) {
      return sell_id < other.sell_id;
    }
    return p < other.p;
  }
};

int main() {
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
  int tt;
  scanf("%d", &tt);
  int gp = 0;
  set <Order, cmp> buys;
  set <Order, cmp> sells;
  while (tt--) {
    Order a;
    scanf("%d %d %d %d %d", &a.id, &a.t, &a.p, &a.v, &a.tv);
    vector <Trade> trades;
    set <Order, cmp> &theset = (a.t == 2 ? buys : sells);
    while (a.v > 0 && !theset.empty()) {
      Order b = *(theset.begin());
      int bp = (a.t == 2 ? -b.p : b.p);
      if ((a.t == 2 && bp < a.p) || (a.t == 1 && bp > a.p)) {
        break;
      }
      vector <Order> after;
      while (a.v > 0 && !theset.empty()) {
        Order b = *(theset.begin());
        if ((a.t == 2 ? -b.p : b.p) != bp) {
          break;
        }
        theset.erase(theset.begin());
        int vt = min(a.v, b.cv);
        trades.push_back(Trade {b.id, a.id, (a.t == 2 ? -b.p : b.p), vt});
        a.v -= vt;
        b.v -= vt;
        b.cv -= vt;
        if (b.v == 0) {
          continue;
        }
        if (b.cv == 0) {
          b.cv = min(b.v, b.tv);
          b.pr = gp++;
        }
        after.push_back(b);
      }
      if (a.v == 0) {
        for (int i = 0; i < (int) after.size(); i++) {
          theset.insert(after[i]);
        }
        continue;
      }
      if (after.empty()) {
        continue;
      }
      long long total = 0;
      for (int i = 0; i < (int) after.size(); i++) {
        total += after[i].v;
      }
      if (total <= a.v) {
        for (int i = 0; i < (int) after.size(); i++) {
          Order b = after[i];
          trades.push_back(Trade {b.id, a.id, (a.t == 2 ? -b.p : b.p), b.v});
        }
        a.v -= total;
        continue;
      }
      int low = 0, high = (int)1.01e9;
      while (low < high) {
        int mid = (low + high + 1) >> 1;
        long long total = 0;
        for (int i = 0; i < (int) after.size(); i++) {
          Order b = after[i];
          total += min(b.v * 1LL, mid * 1LL * b.cv);
        }
        if (total > a.v) {
          high = mid - 1;
        } else {
          low = mid;
        }
      }
      long long cnt = low;
      for (int i = 0; i < (int) after.size(); i++) {
        Order b = after[i];
        if (cnt > 0) {
          int z = (int) min(b.v * 1LL, cnt * 1LL * b.cv);
          trades.push_back(Trade {b.id, a.id, (a.t == 2 ? -b.p : b.p), z});
          b.v -= z;
          a.v -= z;
        }
        if (b.v > 0) {
          b.cv = min(b.v, b.tv);
          theset.insert(b);
        }
      }
    }
    if (a.v > 0) {
      a.cv = min(a.v, a.tv);
      a.pr = gp++;
      if (a.t == 2) {
        sells.insert(a);
      } else {
        a.p = -a.p;
        buys.insert(a);
      }
    }
    sort(trades.begin(), trades.end());
    int j = 0;
    for (int i = 0; i < (int) trades.size(); i++) {
      if (j > 0 && trades[i].buy_id == trades[j - 1].buy_id && trades[i].sell_id == trades[j - 1].sell_id) {
        trades[j - 1].v += trades[i].v;
      } else {
        trades[j++] = trades[i];
      }
    }
    trades.resize(j);
    for (int i = 0; i < (int) trades.size(); i++) {
      Trade t = trades[i];
      if (a.t == 1) {
        swap(t.buy_id, t.sell_id);
      }
      printf("%d %d %d %d\n", t.buy_id, t.sell_id, t.p, t.v);
    }
  }
  printf("\n");
  for (auto x : buys) {
    x.p = -x.p;
    sells.insert(x);
  }
  for (auto x : sells) {
    x.p = abs(x.p);
    printf("%d %d %d %d %d %d\n", x.id, x.t, x.p, x.v, x.tv, x.cv);
  }
  return 0;
}
