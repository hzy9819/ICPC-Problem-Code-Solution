#include <cmath>
#include <ctime>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <climits>

#include <set>
#include <map>
#include <stack>
#include <queue>
#include <vector>
#include <bitset>
#include <complex>
#include <iostream>
#include <algorithm>

#define fi first
#define se second
#define pb push_back
#define lowbit(x) ((x) & -(x))
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define debug(x) cerr << #x << " = " << (x) << endl
#define rep(i, s, t) for (int i = (s), _t = (t); i < _t; ++i)
#define per(i, s, t) for (int i = (t) - 1, _s = (s); i >= _s; --i)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> veci;

const int inf = (int)1e9;
const int dxy[] = { -1, 0, 1, 0, -1 };
const ll INF = 1LL << 60;
const db pi = acos(-1.0);
const db eps = 1e-8;

template<class T>void rd(T &x)
{
	x = 0;
	char c;
	while (c = getchar(), c < '0');
	do
	{
		x = x * 10 + (c^'0');
	}
	while(c = getchar(), c >= '0');
}

// 只能输出整型非负数
template<class T>void pt(T x)
{
	if (!x)
	{
		putchar('0');
		return;
	}
	static char stk[65];
	int tp = 0;
	for(; x; x /= 10) stk[tp++] = x % 10;
	per(i, 0, tp) putchar(stk[i]^'0');
}

template<class T>inline void pts(T x)
{
	pt(x);
	putchar(' ');
}

template<class T>inline void ptn(T x)
{
	pt(x);
	putchar('\n');
}

template<class T>inline void Max(T &a,T b)
{
	if(b > a) a = b;
}

template<class T>inline void Min(T &a,T b)
{
	if(b < a) a = b;
}
// EOT

const int N = (int) 1e6 + 5;

int n;
ll val[N];

int tot_edge,lst[N];
pii edge[N<<1];
ll ans[N];
ll bit[N];
int dep[N];
int par[N];

struct Query
{
	int id,K,flag;
	ll pre;
	Query(){}
	Query(int id, int K, int flag): id(id), K(K), flag(flag){};
};

vector<Query> query[N];

void add_edge(int u, int v)
{
	edge[tot_edge] = pii(v, lst[u]);
	lst[u] = tot_edge++;
}

void add_edges(int u, int v)
{
	add_edge(u, v);
	add_edge(v, u);
}

ll bit_query(int x)
{
	Min(x,n);
	ll res = 0;
	for(;x;x-=lowbit(x))
	{
		res+=bit[x];
	}
	return res;
}

void bit_upd(int x,ll val)
{
	for (;x<=n;x+=lowbit(x))
	{
		bit[x]+=val;
	}
}

void pre_dfs(int u)
{
	for (int i = lst[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if (v==par[u]) continue;
		dep[v]=dep[u]+1;
		par[v]=u;
		pre_dfs(v);
	}
}

void dfs(int u)
{
	rep(i,0,query[u].size())
	{
		int K = query[u][i].K;
		ll res = bit_query(dep[u]+K)-bit_query(dep[u]-1);
		query[u][i].pre=res;
	}
	bit_upd(dep[u],val[u]);
	for (int i = lst[u];~i;i=edge[i].se)
	{
		int v=edge[i].fi;
		if (v==par[u]) continue;
		dfs(v);
	}
	rep(i,0,query[u].size())
	{
		int K = query[u][i].K;
		int id = query[u][i].id;
		int flag = query[u][i].flag;
		ll res = bit_query(dep[u]+K)-bit_query(dep[u]-1);
		res -= query[u][i].pre;
		ans[id]+=flag*res;
	}
}

int main()
{
	scanf("%d",&n);
	rep(i,1,n+1)
	{
		rd(val[i]);
		lst[i]=-1;
	}
	for(int i = 1,u,v;i<n;++i)
	{
		rd(u),rd(v);
		add_edges(u,v);
	}
	int q;
	scanf("%d",&q);
	dep[1]=1;
	pre_dfs(1);
	rep(i,0,q)
	{
		int u, K;
		scanf("%d%d",&u,&K);
		int pre = 0;
		rep(j,0,K+1)
		{
			if (!u) break;
			query[u].pb(Query(i,K-j,1));
			if (pre&&K-j-1>=0) query[pre].pb(Query(i,K-j-1,-1));
			pre = u;
			u = par[u];
		}
	}
	dfs(1);
	rep(i,0,q)ptn(ans[i]);
	return 0;
}