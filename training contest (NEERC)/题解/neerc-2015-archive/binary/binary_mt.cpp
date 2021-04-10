#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

int B = 1;
const int fm = (1LL << B) - 1;

void norm(vi &c) {
    forn(i, (int)c.size() - 1) {
        c[i + 1] += c[i] >> B;
        c[i] &= fm;
    }
//    while (!c.empty() && !c.back()) c.pop_back();
}

void trim(vi &c, int x) {
    c.resize(x / B + 1);
    c[x / B] &= (1LL << (x % B)) - 1;
}

vi add(const vi &a, const vi &b, int k) {
    vi c(max(a.size(), b.size()) + 1);
    forn(i, c.size()) {
        if (i < (int)a.size()) c[i] += a[i];
        if (i < (int)b.size()) c[i] += b[i];
    }
    norm(c);
    trim(c, k);
    return c;
}

int get_bit(const vi &v, int b) {
    return (v[b / B] >> (b % B)) & 1;
}

vi mul(const vi &a, int x, int k) {
    vi b = a;
    b.pb(0);
    forn(i, b.size()) b[i] *= x;
    norm(b);
    trim(b, k);
    return b;
}

void gen(vi n, const vector<vi> &p, int k, int i, vector<pair<int, vi> > &v) {
    if (i == k) {
        n.resize(k + 1);
        if (get_bit(n, k)) v.pb(mp(k, n));
        return;
    }
    if (get_bit(n, i)) return;
    gen(n, p, k, i + 1, v);
    if (i) gen(add(n, p[i], k + 1), p, k, i + 1, v);
}

void print(const vi &v, int k) {
    ford(i, k + 1) {
        cerr << get_bit(v, i);
    }
    cerr << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;

    freopen("binary.in", "rt", stdin);
    freopen("binary.out", "wt", stdout);

    int n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
        return 0;
    }
    --n;

    vector<pair<int, vi> > v;
    for (int k = 1; n / 2 >= (int)v.size(); ++k) {
        vi n(k / B + 1);
        n[k / B] = 1LL << (k % B);
        vector<vi> p(k + 1);
//        p.pb(vi(k / B));
        p[0].pb(1);
        trim(p[0], k + 1);

        forn(i, k) p[i + 1] = mul(p[i], 10, k + 1);
        gen(n, p, k, 0, v);
//        cerr << k << ' ' << v.size() - pv << '\n';
    }
    forn(i, v.size()) reverse(all(v[i].se));
    sort(all(v));

    --n;
    vi w = v[n / 2].se;
    reverse(all(w));
    if (n & 1) w[0] ^= 1;
    ford(k, v[n / 2].fi + 1) cout << get_bit(w, k);
    cout << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
