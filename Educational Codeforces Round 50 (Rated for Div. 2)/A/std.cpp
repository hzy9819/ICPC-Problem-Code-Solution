#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;

LL n,k;

int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);

	scanf("%I64d%I64d",&n,&k);
	printf("%I64d",k%n?k/n+1:k/n);
	
	return 0;
}
