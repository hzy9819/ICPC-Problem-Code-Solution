#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
#define nn 4002
#define nl NULL
#define pn 100002
using namespace std;

struct fnode{
	int n,f,id;
	fnode* next;
	fnode() {n=f=id=0; next=nl; }
};fnode* fa[nn];
fnode put[pn];
int pt=0;

void flow_add_(int x,int y,int f)
{
	fnode* p=&put[pt++]; p->n=y; p->f=f; p->id=pt-1;
	if(fa[x]!=nl) p->next=fa[x];
	fa[x]=p;
}

void flow_add(int x,int y,int f)
{
	flow_add_(x,y,f);
	flow_add_(y,x,0);
}

struct node{
	int n;
	node* next;
	node() {n=0; next=nl; }
};node* a[nn];
map<int,int> M,M2;
vector<int> Q1,Q2,v[nn];
int w[nn][nn];
int n,k,tt,cir[nn],b[nn],K[nn],A[nn];
int dep,sta[nn],dis[nn];

int read() {
	int w = 0, f = 0; char c = getchar();
	while(c != '-' && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void add(int x,int y)
{
	node* p=new node; p->n=y;
	if(a[x]!=nl) p->next=a[x];
	a[x]=p;
}

void dfs(int u,int fa)
{
	if(b[u])
	{
		if(cir[u]) return;
		int top=dep;
		while(top&&sta[top]!=u) cir[sta[top]]=1,top--;
		cir[u]=1;
		return;
	}
	b[u]=1;
	sta[++dep]=u;	
	for(node* p=a[u];p!=nl;p=p->next)
	{
		if(p->n==fa) continue;	  
		dfs(p->n,u);
	}
	sta[dep--]=0;
}

queue<int> Q;
bool Bfs(int ss)
{
	int j;
	memset(b,0,sizeof(b));
	memset(dis,-1,sizeof(dis));
	while(!Q.empty()) Q.pop();
	Q.push(ss);
	dis[ss]=0;
	while(!Q.empty())
	{
		j=Q.front(); Q.pop();
		for(fnode* p=fa[j];p!=nl;p=p->next)
		{
			if(p->f>0&&dis[p->n]<0)
			{
				dis[p->n]=dis[j]+1;
				Q.push(p->n);
			}
		}
	}
	if(dis[tt]<0) return 0;
	else return 1;
}

int Dfs(int u,int maxf)
{
	if(!maxf) return 0;
	if(u==tt) return maxf;
	int t=0,sum=0;
	for(fnode* p=fa[u];p!=nl;p=p->next)
	{
		if(p->f>0&&dis[u]<dis[p->n]&&Dfs(p->n,t=min(p->f,maxf)))
		{
			p->f-=t;
			put[p->id^1].f+=t;
			maxf-=t;
			sum+=t;
			if(!maxf) return sum;
		}
	}
	if(!sum) dis[u]=-1;
	return sum;
}

int main() {
	Hzy("L");
	int x,y;
	scanf("%d%d\n",&n,&k);
	tt=n+k+1;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",A+i,&y);
		add(i,A[i]);
		add(A[i],i);
		for(int j=1;j<=y;++j)
		{
			scanf("%d",&x);
			v[i].push_back(x);
		}
	}
	for(int i=1;i<=k;++i)
	{
		scanf("%d",&K[i]);
		M[K[i]]++;
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		for(auto x:v[i])
		{
			if(M[x]>0)
			{
				if(M2.count(x)==0) M2[x]=++cnt;
				flow_add(i,n+M2[x],1);
			}
		}
	}
	for(auto x:M)
	{
		if(M2.count(x.first)==0) continue;
		flow_add(n+M2[x.first],tt,x.second);
	}
	dep=0;
	dfs(1,-1);
	for(int i=1;i<=n;++i) if(cir[i]) Q1.push_back(i);else Q2.push_back(i);
	bool anc=0;
	int tmp=0;
	for(auto x:Q2)
	{
		Bfs(x);
	   	tmp=Dfs(x,1);
	   	if(tmp==0) {anc=1; break; }
	}
	int t=0;
	if(!anc)
	{
		for(auto x:Q1)
		{
			Bfs(x);
			tmp=Dfs(x,1);
			if(tmp==0)
			{
				t++;
				if(t>=2)
				{
					anc=1;
					break;
				}
			}
		}
	}
	if(anc)
	{
		printf("-1");
	}
	else
	{
		bool anc=0;
		for(int i=1;i<=k;++i)
		{
			anc=0;
			if(M2.count(K[i])==0)
			{
				printf("0 0\n");
				continue;
			}
			int x=n+M2[K[i]];
			for(fnode* p=fa[x];p!=nl;p=p->next)
			{
				if(p->f>0&&p->n<=n)
				{
					printf("%d %d\n",p->n,A[p->n]);
					p->f=0;
					anc=1;
					break;
				}
			}
			if(!anc) printf("0 0\n"); 
		}
	}
   
	return 0;
}
