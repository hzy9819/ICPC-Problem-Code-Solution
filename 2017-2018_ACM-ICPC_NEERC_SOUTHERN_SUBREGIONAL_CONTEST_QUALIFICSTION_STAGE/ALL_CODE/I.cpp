#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 252
#define ln 1000002
using namespace std;

int t,n,m,q,p;
int a[nn][nn],b[nn][nn],qx[ln],qy[ln],ans[nn][nn];
int hx[ln],hy[ln],hs[ln],s[ln];

void bfs(int x,int y,int sp)
{
	memset(b,0,sizeof(b));
	int l=0,r=1,ss=0;
	hx[1]=x,hy[1]=y,hs[1]=sp;
	b[x][y]=1;
	ans[x][y]+=sp;
	while(l<r)
	{
		l++;
		x=hx[l],y=hy[l];
		ss=hs[l];
		if(ss/2<=0) continue;
		if(x>1&&a[x-1][y]&&!b[x-1][y])
		{
			b[x-1][y]=1;
			r++;
			hx[r]=x-1,hy[r]=y,hs[r]=ss/2;
			ans[x-1][y]+=hs[r];
		}
		if(x<n&&a[x+1][y]&&!b[x+1][y])
		{
			b[x+1][y]=1;
			r++;
			hx[r]=x+1,hy[r]=y,hs[r]=ss/2;
			ans[x+1][y]+=hs[r];
		}
		if(y>1&&a[x][y-1]&&!b[x][y-1])
		{
			b[x][y-1]=1;
			r++;
			hx[r]=x,hy[r]=y-1,hs[r]=ss/2;
			ans[x][y-1]+=hs[r];
		}
		if(y<m&&a[x][y+1]&&!b[x][y+1])
		{
			b[x][y+1]=1;
			r++;
			hx[r]=x,hy[r]=y+1,hs[r]=ss/2;
			ans[x][y+1]+=hs[r];
		}		
	}
}

int main()
{
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);

	t=0;
	scanf("%d%d%d%d\n",&n,&m,&q,&p);
	char c;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			scanf("%c",&c);
			if(c=='.') a[i][j]=1;
			if(c=='*') a[i][j]=0;
			if(c>='A'&&c<='Z') a[i][j]=1,qx[++t]=i,qy[t]=j,s[t]=(c-'A'+1)*q;
		}
		scanf("\n");
	}
	for(int i=1;i<=t;++i)
		bfs(qx[i],qy[i],s[i]);
	int sum=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(ans[i][j]>p) sum+=1;
		}
	}
	printf("%d",sum);
	
	return 0;
}
