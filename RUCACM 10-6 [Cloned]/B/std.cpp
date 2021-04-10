#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3fLL
#define pa pair<int,int>
using namespace std;
const int maxn = 510;
int n,m,k;
char s[maxn][2010];
int main()
{
    int T,cas=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        scanf("%s",s[i]);
        int m=n-1;
        while(m&&strstr(s[m],s[m-1])!=NULL) m--;
        m++;
        for(int i=m-1;i>=0&&m<n;i--)
        while(m<n&&strstr(s[m],s[i])==NULL) m++;
        if(m==1) m=-1;
        printf("Case #%d: %d\n",cas++,m);
    }
    return 0;
}
