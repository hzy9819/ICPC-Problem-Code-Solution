#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 502
#define ln 22
using namespace std;

char s[nn][ln];
double a[nn],b[nn];
int n,nu[nn];

bool comp(int _,int __)
{
	return b[_]<b[__];
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);

	scanf("%d\n",&n);
	double ans=1e9;
	int x,bo=0;
	for(int i=1;i<=n;++i)
	{
		scanf("%s%lf%lf\n",s[i],&a[i],&b[i]);
	}
	for(int i=1;i<=n;++i) nu[i]=i;
	sort(nu+1,nu+n+1,comp);
	for(int i=1;i<=n;++i)
	{
		bool anc=0;
		for(int j=1;j<=3;++j) if(nu[j]==i) anc=1;
		if(anc)
		{
			if(a[i]+b[nu[1]]+b[nu[2]]+b[nu[3]]+b[nu[4]]-b[i]<ans)
				ans=a[i]+b[nu[1]]+b[nu[2]]+b[nu[3]]+b[nu[4]]-b[i],x=i,bo=1;
		}
		else
		{
			if(a[i]+b[nu[1]]+b[nu[2]]+b[nu[3]]<ans)
				ans=a[i]+b[nu[1]]+b[nu[2]]+b[nu[3]],x=i,bo=0;
		}
	}
	printf("%lf\n",ans);
	if(!bo)
	{
		printf("%s\n",s[x]);
		for(int i=1;i<=3;++i) printf("%s\n",s[nu[i]]);
	}
	else
	{
		printf("%s\n",s[x]);
		for(int i=1;i<=4;++i)
		{
			if(nu[i]==x) continue;
			else printf("%s\n",s[nu[i]]);
		}
	}

	return 0;
}
