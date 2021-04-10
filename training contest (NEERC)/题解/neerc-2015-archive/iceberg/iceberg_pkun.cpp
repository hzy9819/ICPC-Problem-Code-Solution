#include <cstdio>
#include <map>
#include <list>
#include <algorithm>
#include <assert.h>

using namespace std;

#define BUY 1
#define SELL 2

struct order {
    int id;
    int type;
    int price;
    int volume;
    int tvolume;
    int cvolume;
};


typedef list<order> order_queue;

map<int, order_queue> sell_book;
map<int, order_queue> buy_book;


map<pair<int,int>, pair<int, int>> current;

void fix_cvolume(order&q) {
    q.cvolume = (q.cvolume % q.tvolume + q.tvolume) % q.tvolume;
    if (q.cvolume > q.volume) {
        q.cvolume = q.volume;
    }
}

void match_two(order& q, order& other, int tv) {
    int buy_id = q.type == BUY ? q.id : other.id;
    int sell_id = q.id + other.id - buy_id;
    int price = other.price; //q.type == BUY ? q.price : other.price;
    if (current.find(make_pair(buy_id, sell_id)) != current.end()) {
        current[make_pair(buy_id, sell_id)].second += tv;
    } else {
        current[make_pair(buy_id, sell_id)] = make_pair(price, tv);
    }
    q.volume -= tv;
    other.volume -= tv;
    other.cvolume -= tv;
    fix_cvolume(other);
}

int get_one(const order &q, int iters) {
    return (int) min(q.volume * 1LL, q.cvolume + q.tvolume * 1LL * (iters - 1));
}



int get_total(const order_queue& oq, int iters, int limit) {
    int ans = 0;
    for (const order& q : oq) {
        ans += get_one(q, iters);
        if (ans > limit) return ans;
    }
    return ans;
}


void match_order(order& q, order_queue& oq) {
    if (oq.empty()) return;
    int l = 0;
    int r = (int) 1e9;
    while (r - l > 1) {
        int m = (l + r) / 2;
        long long val = get_total(oq, m, q.volume);
        if (val < q.volume)
            l = m;
        else
            r = m;
    }
    for (int it = !l; it < 2 && oq.size(); it++) {
        int mult = it ? 1 : l;
        int first_id = -1;
        while (q.volume > 0 && oq.size()) {
            order &other = oq.front();
            if (first_id == other.id)
                break;
            int tv = min(q.volume, get_one(other, mult));
            match_two(q, other, tv);
            if (other.cvolume == 0) {
                order other_copy = other;
                oq.erase(oq.begin());
                if (other_copy.volume > 0) {
                    other_copy.cvolume = min(other_copy.tvolume, other_copy.volume);
                    oq.push_back(other_copy);
                    if (first_id == -1)
                        first_id = other_copy.id;
                }
            }
        }
        if (it == 0) assert(q.volume);
    }
    assert(q.volume == 0 || oq.size() == 0);
}

int main() {
    freopen("iceberg.in", "r", stdin);
    freopen("iceberg.out", "w", stdout);

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        order q;
        scanf("%d%d%d%d%d",&q.id, &q.type, &q.price, &q.volume, &q.tvolume);
        current.clear();
        if (q.type == SELL) {
            while (!buy_book.empty()) {
                auto it = --buy_book.end();
                if (it->first < q.price) break;
                match_order(q, it->second);
                if (it->second.empty()) {
                    buy_book.erase(it);
                }
                if (q.volume == 0)
                    break;
            }
            if (q.volume > 0) {
                q.cvolume = min(q.volume, q.tvolume);
                sell_book[q.price].push_back(q);
            }
        } else {
            while (!sell_book.empty()) {
                auto it = sell_book.begin();
                if (it->first > q.price) break;
                match_order(q, it->second);
                if (it->second.empty()) {
                    sell_book.erase(it);
                }
                if (q.volume == 0)
                    break;
            }
            if (q.volume > 0) {
                q.cvolume = min(q.volume, q.tvolume);
                buy_book[q.price].push_back(q);
            }
        }

        for (const auto& x : current) {
            printf("%d %d %d %d\n", x.first.first, x.first.second, x.second.first, x.second.second);
        }
    }

    printf("\n");
    for (const auto &x : buy_book) {
        for (const order &y : x.second) {
            printf("%d %d %d %d %d %d\n", y.id, y.type, y.price, y.volume, y.tvolume, y.cvolume);
        }
    }
    for (const auto &x : sell_book) {
        for (const order &y : x.second) {
            printf("%d %d %d %d %d %d\n", y.id, y.type, y.price, y.volume, y.tvolume, y.cvolume);
        }
    }
    return 0;
}
