#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define M(x) memset(x,0,sizeof(x))
#define nn 302
#define eps 1e-8
#define LL long long
using namespace std;

int ch[nn][7],sta[nn],f[nn],val[nn];
int cnt,n,T,L;
queue<int> q;

double a[nn][nn],x[nn];

void set()
{
	int u,v;
	while(!q.empty()) q.pop();
	for(int i=1;i<=6;++i)
	{
		if(ch[0][i])
		{
			f[ch[0][i]]=0; q.push(ch[0][i]);
		}
	}
	while(!q.empty())
	{
		u=q.front(); q.pop();
		for(int i=1;i<=6;++i)
		{
			v=ch[u][i];
			if(v)
			{
				int w=f[u];
				while(w&&!ch[w][i]) w=f[w];
				f[v]=ch[w][i];
				q.push(v);
				if(val[f[v]]) val[v]++;
			}else ch[u][i]=ch[f[u]][i];
		}
	}
}

double Abs(double x) {return x>0?x:-x; }
void gauss(int l)
{
	int r;
	for(int k=0;k<=l;++k)
	{
		r=k;
		for(int i=k+1;i<=l;++i) if(Abs(a[i][k])>Abs(a[r][k])+eps) r=i;
		if(r>k) for(int i=k;i<=l+1;++i) swap(a[k][i],a[r][i]);
		if(fabs(a[k][k])<eps) continue;
		for(int i=k+1;i<=l;++i)
			for(int j=l+1;j>=k;--j)
				a[i][j]=a[k][j]*a[i][k]/a[k][k]-a[i][j];
	}
	for(int i=l;i>=0;--i)
	{
		x[i]=a[i][l+1];
		for(int j=i+1;j<=l;++j) x[i]-=x[j]*a[i][j];
		(a[i][i])?x[i]/=a[i][i]:x[i]=0;
	}
}

void work()
{
	M(a); M(x);
	int p;
   	for(int i=0;i<=cnt;++i)
   	{
   		if(val[i]) continue;
   		for(int j=1;j<=6;++j)
   		{
   		   	p=ch[i][j];
   			if(p) a[p][i]+=1.0/6;
   		   	else a[p][i]-=1.0/6;
   		}
   	}
	a[0][0]+=1;
	a[0][cnt+1]=1;
	for(int i=1;i<=cnt;++i) a[i][i]+=-1;
	
		
	gauss(cnt);
}

int main()
{
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);

	int t;
	scanf("%d\n",&T);
	while(T--)
	{
		cnt=0;
		M(f); M(val); M(ch); M(sta);
 		scanf("%d%d\n",&n,&L);
		for(int i=1;i<=n;++i)
		{
			int u=0;
			for(int j=1;j<=L;++j)
			{
				scanf("%d",&t);
				if(ch[u][t]==0) ch[u][t]=++cnt;
				u=ch[u][t];
			}
			val[u]++;
			sta[i]=u;
		}
		set();		
		work();
		
    	for(int i=1;i<=n;++i)
    	{
     		printf("%.6lf ",x[sta[i]]);
			//if(i==n) break;
    		//if(i%4==0) printf("\n");
    		//if(i != n && T) printf(" ");
    	}
		puts("");
	}

	return 0;
}
