#include<cstdio>
#include<cstring>
#include<algorithm>
#define nl NULL
#define nn 200002
#define dn 1050000
#define LL long long
#define orz "%lld"
using namespace std;

struct node{
	int n;
	node* next;
	node() {n=0; next=nl; }
};
node* a[nn];
int rt,adm,n;
int vis[nn],b[nn],tag[nn];
LL ans[nn],t[dn];

void add(int x,int y)
{
	node* p=new node; p->n=y;
	if(a[x]!=nl) p->next=a[x]; a[x]=p;
}

int getroot(int u, int fa, int sn)
{
	int su=1,d=0,dm=0;
	for(node* p=a[u];p!=nl;p=p->next)
	{
		if(p->n!=fa&&!vis[p->n])
		{
			d=getroot(p->n,u,sn);
			su+=d;
			if(d>dm) dm=d;
		}
	}
	dm=max(dm,sn-su);
	if(dm<adm) adm=dm,rt=u;
	return su;
}

int find(int u, int fa, int pr, int c)
{
	int su=1;
	t[c^=b[u]]+=pr;
    for(node* p=a[u];p!=nl;p=p->next)
	{
		if(p->n!=fa&&!vis[p->n]) su+=find(p->n,u,pr,c);
	}
	return su;
}

LL work(int u, int fa, int c)
{
	c^=b[u];
	LL sum=t[c];
	for(int i=0;i<20;++i) sum+=t[c^(1<<i)];
	for(node* p=a[u];p!=nl;p=p->next)
	{
		if(p->n!=fa&&!vis[p->n]) sum+=work(p->n,u,c);
	}
	ans[u]+=sum;
	return sum;
}

void dfs(int u, int sn)
{
	for(node* p=a[u];p!=nl;p=p->next) if(!vis[p->n]) tag[p->n]=find(p->n,u,1,0);
	LL sum=0;
	sum+=t[b[u]];
	for(int i=0;i<20;++i) sum+=t[b[u]^(1<<i)];
	t[0]++;//from u
	for(node* p=a[u];p!=nl;p=p->next)
	{
		if(!vis[p->n])
		{
			find(p->n,u,-1,0);
			sum+=work(p->n,u,b[u]);
			find(p->n,u,1,0);
		}
	}
	t[0]--;
	ans[u]+=sum/2;
	vis[u]=1;
	for(node* p=a[u];p!=nl;p=p->next) if(!vis[p->n]) find(p->n,u,-1,0);
	for(node* p=a[u];p!=nl;p=p->next)
	{
		if(vis[p->n]) continue;
		rt=0; adm=n;
		getroot(p->n,-1,tag[p->n]);
		dfs(rt,tag[p->n]);
	}
}

int main()
{
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);

	int u,v;
	scanf("%d\n",&n);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d\n",&u,&v);
		add(u,v), add(v,u);
	}
	char ch;
	for(int i=1;i<=n;++i) scanf("%c",&ch),b[i]=1<<(ch-'a'),ans[i]=1;
	adm=n;
	getroot(1,-1,n);
	dfs(rt,n);
	for(int i=1;i<=n;++i) printf(orz" ",ans[i]);
	
	return 0;
}
