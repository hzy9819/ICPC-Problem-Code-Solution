#include<iostream>
#include <cstring>
#include <string>
#include <cstdio>
#define LL long long
using namespace std;
const LL K=99;
double dp[12][K][2];//0: at least 1:dead all
int s[12];
double p[12];
double fastMi(double a,int b)
{
    double mut=1;
    while(b)
    {
        if(b%2!=0)
            mut*=a;
        a*=a;
        b/=2;
    }
    return mut;
}
int main()
{
	freopen("D.in", "r", stdin), freopen("ans.out", "w", stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0; i<n; i++)
            scanf("%d %lf",&s[i],&p[i]);
        for(int i=0; i<n; i++)
        {
            for(int k=0; k<K; k++)
            {
                dp[i][k][1]=fastMi(1-fastMi(p[i],k),s[i]);
                dp[i][k][0]=1-dp[i][k][1];
            }
        }
        if(n==1)
        {
            puts("1.000000");
            continue;
        }
        for(int i=0; i<n; i++)
        {
            double ans=0.0;
            for(int k=1; k<K-1; k++)
            {
                double px=dp[i][k][0]-dp[i][k+1][0];
                for(int j=0; j<n; j++)
                {
                    if(j==i)continue;
                    px*=dp[j][k][1];
                }
                ans+=px;
            }
            if(i==n-1)
                printf("%.6f\n",ans);
            else printf("%.6f ",ans);
        }

    }
     return 0;
}
