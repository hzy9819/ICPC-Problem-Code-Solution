#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define nn 402
#define ln 32
using namespace std;

int n,a,b,k,f;
priority_queue <int> Q;
char s1[nn][ln],s2[nn][ln];
int w[nn],h[nn],s[nn];

bool strcm(char* sa,char* sb)
{
	int la=strlen(sa),lb=strlen(sb);
	if(la!=lb) return 0;
	for(int i=0;i<la;++i) if(sa[i]!=sb[i]) return 0;
	return 1;
}

int main()
{
	//freopen("K.in","r",stdin);
	//freopen("K.out","w",stdout);

	int ans=0;
	scanf("%d%d%d%d%d\n",&n,&a,&b,&k,&f);
	for(int i=1;i<=n;++i)
	{
		scanf("%s%s\n",s1[i],s2[i]);
		if(i>1&&strcm(s2[i-1],s1[i])) w[i]=b;else w[i]=a;
		ans+=w[i];
	}
	for(int i=1;i<=n;++i)
	{
		//v[i].push_back(i);
		if(h[i]) continue;
		s[i]=w[i];
		h[i]=i;
		for(int j=i+1;j<=n;++j)
		{
			if((strcm(s1[i],s1[j])&&strcm(s2[i],s2[j]))||(strcm(s1[i],s2[j])&&strcm(s2[i],s1[j])))
			{
				//v[i].push_back(j);
				s[i]+=w[j];
				h[j]=h[i];
			}
		}
		Q.push(s[i]);
	}
	for(int i=1;i<=k;++i)
	{
		if(Q.empty()) break;
		if(Q.top()<=f) break;
		ans-=Q.top()-f; Q.pop();
	}
	printf("%d",ans);
	
	return 0;
}
