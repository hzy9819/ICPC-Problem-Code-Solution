#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 300002
using namespace std;

int n,k,t[nn],v[nn],s[nn],f[nn],ans;

bool comp(int _,int __)
{
	return _<__;
}

int find(int x)
{
	int l,r,mid;
	for(int i=1;i<=n;++i)
	{
		l=1,r=i-k+1,mid=(l+r)/2;
		t[i]=0;
		while(l<=r)
		{
			if(v[i]-v[mid]<=x) t[i]=mid,r=mid-1;
			else l=mid+1;
			mid=(l+r)/2;
		}
		if(v[i]-v[i-k+1]>x) t[i]=0;
	}
	for(int i=1;i<=n;++i) f[i]=s[i]=0;
	f[0]=s[0]=1;
	for(int i=1;i<=n;++i)
	{
		s[i]=s[i-1];
		if(t[i]>i-k+1||!t[i]) continue;
		if((t[i]>1&&s[i-k]-s[t[i]-2]>0)||(t[i]==1&&s[i-k]>0)) f[i]=1;else f[i]=0;
		s[i]+=f[i];
	}
	if(f[n]) return 1;else return 0;
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	scanf("%d%d\n",&n,&k);
	for(int i=1;i<=n;++i) scanf("%d",v+i);
	sort(v+1,v+n+1,comp);
	int l=0,r=(int)1e+9,mid=(l+r)/2;
	ans=0;
	find(20);
	while(l<=r)
	{
		if(find(mid)) ans=mid,r=mid-1;
		else l=mid+1;
		mid=(l+r)/2;
	}
	printf("%d",ans);

	return 0;
}
