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
 
struct cmp_buys {
  bool operator() (const Order& lhs, const Order& rhs) const {
    if (lhs.p != rhs.p) {
      return lhs.p > rhs.p;
    }
    return lhs.pr < rhs.pr;
  }
};
 
struct cmp_sells {
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
  set <Order, cmp_buys> buys;
  set <Order, cmp_sells> sells;
  while (tt--) {
    Order a;
    scanf("%d %d %d %d %d", &a.id, &a.t, &a.p, &a.v, &a.tv);
    vector <Trade> trades;
    if (a.t == 2) {
      while (a.v > 0 && !buys.empty()) {
        Order b = *(buys.begin());
        if (b.p < a.p) {
          break;
        }
        buys.erase(buys.begin());
        int vt = min(a.v, b.cv);
        trades.push_back(Trade {b.id, a.id, b.p, vt});
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
        buys.insert(b);
      }
      if (a.v > 0) {
        a.cv = min(a.v, a.tv);
        a.pr = gp++;
        sells.insert(a);
      }
    } else {
      while (a.v > 0 && !sells.empty()) {
        Order b = *(sells.begin());
        if (b.p > a.p) {
          break;
        }
        sells.erase(sells.begin());
        int vt = min(a.v, b.cv);
        trades.push_back(Trade {a.id, b.id, b.p, vt});
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
        sells.insert(b);
      }
      if (a.v > 0) {
        a.cv = min(a.v, a.tv);
        a.pr = gp++;
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
      printf("%d %d %d %d\n", t.buy_id, t.sell_id, t.p, t.v);
    }
  }
  printf("\n");
  for (auto x : buys) {
    sells.insert(x);
  }
  for (auto x : sells) {
    printf("%d %d %d %d %d %d\n", x.id, x.t, x.p, x.v, x.tv, x.cv);
  }
  return 0;
}
