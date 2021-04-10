#include<cstdio>
#include<cstring>
#include<algorithm>
#define nn 1002
using namespace std;

int n,m,h[nn],b[nn],ans;
char s[nn],t[nn],a[nn][nn];

int stcmp(char* s,char* t)
{
	for(int i=0;i<n;++i) if(s[i]!=t[i]) return 0;
	return 1;
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	scanf("%d\n",&n);
	scanf("%s\n%d\n",s,&m);
	for(int i=1;i<=m;++i) scanf("%s\n",a[i]);
	for(int i=0;i<n;++i)
	{
		if(s[i]!='*') h[s[i]-'a']++;
	}
	for(int i=1;i<=m;++i)
	{
		for(int j=0;j<n;++j)
		{
			if(h[a[i][j]-'a']) t[j]=a[i][j];else t[j]='*';
		}
		if(stcmp(s,t)) b[i]=1;else b[i]=0;
	}
	int anc=0,ani=0;
	ans=0;
	for(int k=0;k<26;++k)
	{
		anc=ani=0;
		if(h[k]) continue;
    	for(int i=1;i<=m;++i)
    	{
    		if(!b[i]) continue;
			anc=0;
    		for(int j=0;j<n;++j)
    		{
    			if(h[a[i][j]-'a']) continue;
    			if(s[j]=='*'&&a[i][j]-'a'==k) {anc=1; break; }
    		}
			if(!anc) {ani=1; break;}
    	}
		if(!ani) ans++;
	}
	printf("%d",ans);

	return 0;
}
