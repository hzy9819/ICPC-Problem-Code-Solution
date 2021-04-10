#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 1000002
using namespace std;

int n,q,a[nn];

int gcd(int a,int b) {if(!b) return a;else return gcd(b,a%b); }

int find(int l,int r,int x)
{
	for(l+=n, r+=n;l < r;l>>=1, r>>=1)
	{
		if(l&1)
		{
			if(a[l] % x) return 0;
			else l++;
		}
		if(r&1)
		{
			if(a[r-1] % x) return 0;
			else r--;
		}
	}
	return 1;
}

int main()
{
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);

	scanf("%d\n",&n);
	for(int i=0;i<n;++i) scanf("%d",&a[n+i]);//n...2n-1
	for(int i=n-1;i>0;--i) a[i]=gcd(a[i<<1], a[i<<1|1]);
	scanf("%d\n",&q);
	int op,l,r,x,y,mid;
	for(int i=1;i<=q;++i)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d%d%d\n",&l,&r,&x);
			int li=l-1,ri=r;
			while(ri-li>1)
			{
				mid=(li+ri)/2;
				if(find(li,mid,x)) li=mid;else ri=mid;
			}
			if(ri == r || find(ri,r,x)) printf("YES\n");else printf("NO\n");
		}
		else
		{
			scanf("%d%d\n",&l,&y);
			l=l+n-1;
			a[l]=y, l>>=1;
			while(l) a[l]=gcd(a[l<<1],a[l<<1|1]), l>>=1;
		}
	}

	return 0;
}
