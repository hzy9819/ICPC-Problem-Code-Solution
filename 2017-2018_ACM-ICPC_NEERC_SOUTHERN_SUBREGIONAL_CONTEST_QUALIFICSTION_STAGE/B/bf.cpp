#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 200002
using namespace std;

int n,bs;
int a[nn],b[nn],sta[nn];

int main()
{
	freopen("B.in","r",stdin);
	freopen("bf.out","w",stdout);

	scanf("%d\n",&n);
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	int top=0;
	while(1)
	{
		top=bs=0;
		for(int i=1;i<=n;++i)
		{
			if(b[i]) continue;
			if(!bs||bs<a[i]) bs=a[i],sta[++top]=i;
		}
		if(!bs) break;
		for(int i=1;i<=top;++i) b[sta[i]]=1,printf("%d ",a[sta[i]]);
		printf("\n");
	}
	
	return 0;
}
