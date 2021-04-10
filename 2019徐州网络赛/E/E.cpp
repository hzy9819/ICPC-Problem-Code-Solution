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

const int N = (int) 5e5 + 5;

int val[N];
int tot;
int disc[N<<1];
int ans[N];
int bit[N<<1];

int query(int x)
{
	int res = 0;
	for (; x; x-=lowbit(x))
	{
		Max(res,bit[x]);
	}
	return res;
}

void upd(int x,int val)
{
	for(; x<=tot;x+=lowbit(x))
	{
		Max(bit[x],val);
	}
}

int main()
{
	freopen("E.in", "r", stdin), freopen("std.out", "w", stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,n+1)
	{
		scanf("%d",&val[i]);
		disc[tot++]=val[i];
		disc[tot++]=val[i]+m;
	}
	sort(disc,disc+tot);
	tot=unique(disc,disc+tot)-disc;
	per(i,1,n+1)
	{
		int cur = lower_bound(disc,disc+tot,val[i])-disc+1;
		cur = tot-cur+1;
		int tar = lower_bound(disc,disc+tot,val[i]+m)-disc+1;
		tar = tot-tar+1;
		int res = query(tar);
		if(!res)ans[i]=-1;
		else ans[i]=res-i-1;
		upd(cur,i);
	}
	rep(i,1,n+1)
	{
		printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
