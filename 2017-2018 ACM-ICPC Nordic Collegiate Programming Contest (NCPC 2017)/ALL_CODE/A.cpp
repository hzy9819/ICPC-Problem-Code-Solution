#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
#define nn 500002
using namespace std;

db f[nn],s[nn],ds[nn],l,a,b,t,r;
int n,pre[nn],ans[nn],ls[nn],p1,p2;

void pop(int x)
{
	while(p1<=p2&&ls[p1]<=x) p1++;
}

void push(int x,db d)
{
	while(p2>=p1&&ds[p2]>=d) p2--;
	ls[++p2]=x,ds[p2]=d;
}

void head(int& x,double& d)
{
	if(p1<=p2) x=ls[p1],d=ds[p1];else x=0,d=1e12;
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);

	scanf("%lf%lf%lf%lf",&l,&a,&b,&t);
	scanf("%lf",&r);
	scanf("%d\n",&n);
	for(int i=1;i<=n;++i) scanf("%lf",s+i);
	for(int i=1;i<=n;++i) f[i]=s[i]/a;
	int p=0,x=0,y=0,q=0;
	double fm=0,tmp=0;
	s[0]=0;
	p1=1,p2=0;
	for(int i=1;i<=n;++i)
	{
		while(q+1<i&&a*t<s[i]-s[q+1])
		{
			q++;
			tmp=f[q]-(a*t+s[q])/b+t;
			push(q,tmp);
		}
		while(p+1<i&&a*t+b*r<s[i]-s[p+1])
		{
			tmp=f[p+1]+r-(b*r+s[p+1])/a;
			if(tmp<fm) fm=tmp,x=p+1;
			p++;
			pop(p);
		}
		head(y,tmp);
		f[i]=tmp+s[i]/b,pre[i]=y;
		if(f[i]>fm+s[i]/a) f[i]=fm+s[i]/a,pre[i]=x;
	}
	f[n+1]=l/a;
	for(int i=1;i<=n;++i)
	{
		if(a*t+b*r<(l-s[i])) tmp=f[i]+r+(l-s[i]-b*r)/a;
		else if(a*t<l-s[i]) tmp=f[i]+(l-s[i]-a*t)/b+t;
		else tmp=f[i]+(l-s[i])/a;
		if(f[n+1]>tmp) f[n+1]=tmp,pre[n+1]=i;
	}
	int r=0;
	x=n+1;
	//printf("%.6lf",f[n+1]);
	
	while(pre[x]) ans[++r]=pre[x],x=pre[x];
	printf("%d\n",r);
	for(int i=r;i>=1;--i) printf("%d ",ans[i]-1);
	
	
	return 0;
}
