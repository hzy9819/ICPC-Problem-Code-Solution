#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 502
#define nl NULL
#define ln 12
using namespace std;

struct node{
	int n;
	node* next;
};node* a[nn];
int fa[nn],st[nn],tg;
int ans,b1,b2,dep,n,tx,sr,cnt,clo;
int t[nn],b[nn];
char ch;
char s[nn][ln],s0[nn];

int stcmp(char* a,char* b)
{
	int l=strlen(a),r=strlen(b);
	if(l!=r) return 0;
	for(int i=0;i<l&&i<r;++i)
	{
		if(a[i]!=b[i]) return 0;
	}
	return 1;
}

void add(int x,int y)
{
	node* p=new node; p->n=y; p->next=nl;
	if(a[x]!=nl) p->next=a[x]; a[x]=p;
}

void bfs(int u,int o=0)
{
	int l=0,r=1;
	memset(t,0,sizeof(t));
	t[1]=u;
	int x,v;
	memset(b,0,sizeof(b));
	b[u]=1;
	while(l<r)
	{
		x=t[++l];
		for(node* p=a[x];p!=nl;p=p->next)
		{
			v=p->n;
			if(v==u)
			{
				if(ans>b[x])
				{
					ans=b[x];
					tx=u;
				}
				else if(ans==b[x]&&o)
				{
					sr=0;
            		while(x&&x!=u) st[++sr]=x,x=fa[x];
            		st[++sr]=u;
					return;
				}
			}
			if(!b[v])
			{
				b[v]=b[x]+1;
				fa[v]=x;
				t[++r]=v;
			}
		}
	}
}


int main()
{
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);

	int l,x;
	memset(a,0,sizeof(a));
	scanf("%d\n",&n);
	for(int i=1;i<=n;++i) scanf("%s",s[i]);
	for(int i=1;i<=n;++i)
	{
		scanf("%s%d\n",s[i],&x);
		for(int j=1;j<=x;++j)
		{
			scanf("%s ",s[0]);
			ch=' ';
			while(ch==' ')
			{
				l=0;
    			while((ch=getchar())>='a'&&ch<='z') s0[l++]=ch;
				s0[l]='\0';
				for(int k=1;k<=n;++k)
				{
					if(stcmp(s0,s[k])) {add(i,k); break; }
				}
				if(ch=='\n') break;
				ch=getchar();
			}
			
		}
	}
	ans=(int)1e9;
	for(int i=1;i<=n;++i)
		bfs(i);
	if(ans==(int)1e9) printf("SHIP IT");
	else
	{
		bfs(tx,1);
		for(int i=sr;i>=1;--i) printf("%s ",s[st[i]]);
	}
	
	return 0;
}
