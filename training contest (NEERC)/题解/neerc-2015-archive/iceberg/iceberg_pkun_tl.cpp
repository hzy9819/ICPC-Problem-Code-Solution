#include <cstdio>
#include <map>
#include <list>

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
}

void match_order(order& q, order_queue& oq) {
    if (oq.empty()) return;
    while (q.volume > 0 && oq.size() > 1) {
        order &other = oq.front();
        int tv = min(q.volume, other.cvolume);
        match_two(q, other, tv);
        if (other.cvolume == 0) {
            order other_copy = other;
            oq.erase(oq.begin());
            if (other_copy.volume > 0) {
                other_copy.cvolume = min(other_copy.volume, other_copy.tvolume);
                oq.push_back(other_copy);
            }
        }
    }
    if (q.volume == 0) return;
    order &other = oq.front();
    int tv = min(other.volume, q.volume);
    match_two(q, other, tv);
    if (other.volume == 0) {
        oq.erase(oq.begin());
    } else {
        other.cvolume = (other.cvolume % other.tvolume + other.tvolume) % other.tvolume;
        if (other.cvolume == 0) {
          other.cvolume = other.tvolume;
        }
        if (other.cvolume > other.volume) {
            other.cvolume = other.volume;
        }
    }
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
