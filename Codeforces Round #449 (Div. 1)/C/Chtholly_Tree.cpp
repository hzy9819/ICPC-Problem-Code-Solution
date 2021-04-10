#include <bits/stdc++.h>
#define LL long long
#define db double
#define mk(a, b) make_pair(a, b)
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int weg = 1000000007;
LL read() {
	LL w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

LL calc(LL x, LL y, const LL & p) {
	x %= p;
	LL res = 1;
	for(; y; y >>= 1, x = x * x % p)
		if(y & 1)
			res = res * x % p;
	return res;
}

int n, m;
LL seed, vmax;

LL rnd() {
	LL ret = seed;
	seed = (seed * 7 + 13) % weg;
	return ret;
}

struct Node_t {
  int l, r;
  mutable LL v;
  Node_t(int il = 0, int ir = -1, LL iv = 0) : l(il), r(ir), v(iv) {}
  inline bool operator<(const Node_t &o) const { return l < o.l; }
};

typedef set<Node_t>::iterator iter;

set <Node_t> s;

inline iter split(int pos){
	iter it = s.lower_bound(Node_t(pos));
	if(it != s.end() && it->l == pos) return it;
	--it;
	int l = it->l, r = it->r;
	LL v = it->v;
	s.erase(it);
	s.insert(Node_t(l, pos - 1, v));
	return s.insert(Node_t(pos, r, v)).first;
}

void assign(int l, int r, LL v) {
  auto itr = split(r + 1), itl = split(l);
  s.erase(itl, itr);
  s.insert(Node_t(l, r, v));
}

void Add(int l, int r, LL x) {
	auto itr = split(r + 1), itl = split(l);
	for(; itl != itr; ++itl)
		itl->v += x;
}

LL k_th(int l, int r, int k) {
	auto itr = split(r + 1), itl = split(l);
	vector< pair<LL, int> > vec;
	vec.clear();
	while(itl != itr) {
		vec.push_back(mk(itl->v, itl->r - itl->l + 1));
		itl++;
	}
	sort(vec.begin(), vec.end());
	for(pair<LL, int> & i : vec) {
		k -= i.second;
		if(k <= 0) return i.first;
	}
	return -1LL;
}

LL sum(int l, int r, LL x, LL y) {
	auto itr = split(r + 1), itl = split(l);
	LL res = 0;
	while(itl != itr) {
		res = (res + calc(itl->v, x, y) * (itl->r - itl->l + 1)) % y;
			   itl++;
	}
	return res;
}

int main() {
	n = read(), m = read(), seed = read(), vmax = read();
	for(int i = 1; i <= n; ++i)
		s.insert(Node_t(i, i, rnd() % vmax + 1));
	int opt, l, r;
	LL x, y;
	for(int i = 1; i <= m; ++i) {
		opt = rnd() % 4 + 1;
		l = rnd() % n + 1;
		r = rnd() % n + 1;
		if(l > r) swap(l, r);
		x = rnd() % ((opt == 3) ? (r - l + 1) : vmax) + 1;
		switch(opt){
			case 1:{
				Add(l, r, x);
				break;
			}
			case 2:{
				assign(l, r, x);
				break;
			}
			case 3:{
				printf("%lld\n", k_th(l, r, x));
				break;
			}
			case 4:{
				y = rnd() % vmax + 1, printf("%lld\n", sum(l, r, x, y));
				break;
			}
			
		}
	}
		
	return 0;
}
