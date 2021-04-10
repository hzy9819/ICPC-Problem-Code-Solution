#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define nn 200002
using namespace std;

LL ans,gsum,sum;
int n,s[nn],g[nn],t[nn],l1[nn],l2[nn],p[nn];

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	sum=0;
	scanf("%d\n",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d\n",s+i,g+i);
		t[i]=s[i]+g[i];
		sum+=1LL*t[i];
		gsum+=1LL*g[i];
	}
	l2[n]=n+t[n];
	l1[n]=s[n]-n;
	int tl,sl;
	for(int i=n-1;i>=1;--i)
	{
		tl=i+t[i];
		sl=s[i]-i;
		l2[i]=min(l2[i+1],tl);
		l1[i]=max(l1[i+1],sl);
	}
	for(int i=1;i<=n;++i)
	{
		if(l2[i]-i<l1[i]+i) {printf("-1"); return 0;}
	}
	LL x;
	x=min(t[1],l2[1]-1);
	p[1]=ans=x;
	for(int i=2;i<=n;++i)
	{
		if(x+1<=l2[i]-i&&x+1>=l1[i]+i) x++,ans+=x;
		else if(x<=l2[i]-i&&x>=l1[i]+i) ans+=x;
		else if(x-1<=l2[i]-i&&x-1>=l1[i]+i) x--,ans+=x;
		else {printf("-1"); return 0;}
		p[i]=x;
	}
	ans=gsum-(sum-ans);
	printf("%I64d\n",ans);
	for(int i=1;i<=n;++i) printf("%d ",p[i]);

	return 0;
}
