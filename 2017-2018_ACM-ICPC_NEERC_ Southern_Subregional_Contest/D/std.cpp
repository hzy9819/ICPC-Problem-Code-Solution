#include <bits/stdc++.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#define N 1010010
#define inf 1000000007
using namespace std;

int n,tot,sum[N],q[N],f[N],ans[2];
char s[N];

int get(int l,int r)
{
	if (l>r) return 0;
	return sum[r]-sum[l-1];
}

bool jd(int w)
{
	int i,j,rt=0,k=0;
	for (i=1;i<=tot;i++){
		if (get(f[i-1]+1,q[i]-w-1)) return 0;
		if (!get(f[i-1]+1,q[i]-1)) f[i]=q[i]+w;
		else if (i>1&&!get(f[i-2]+1,q[i]-w-1)) f[i]=max(q[i-1]+w,q[i]);
		else f[i]=q[i];
	}
	return !get(f[tot]+1,n);
}

int main()
{
	int i,j,k,l,r,mid;
	scanf("%d",&n);
	scanf("%s",s+1);
	tot=0;
	for (i=1;i<=n;i++){
		sum[i]=sum[i-1]+(s[i]=='*'?1:0);
		if (s[i]=='P') q[++tot]=i;
	}
	if (tot==1){
		ans[0]=max(sum[n]-sum[q[1]],sum[q[1]]);
		ans[1]=n;
		k=0;
		for (i=q[1];i<=n;i++) if (s[i]=='*'){
			k++;
			if (k==ans[0]) {
				ans[1]=min(ans[1],i-q[1]);
				break; 
			}
		}
		k=0;
		for (i=q[1];i>0;i--) if (s[i]=='*'){
			k++;
			if (k==ans[0]) {
				ans[1]=min(ans[1],q[1]-i);
				break; 
			}
		}
	}
	else {
		ans[0]=sum[n];
		l=1;r=n;
		while (l<r){
			mid=(l+r)>>1;
			if (jd(mid)) r=mid;
			else l=mid+1;
		}	
		ans[1]=l;	
	}
	printf("%d %d\n",ans[0],ans[1]);
}
