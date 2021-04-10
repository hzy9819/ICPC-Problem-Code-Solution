#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
int n;
LL a[15],b[15];
LL gcd(LL a,LL b){
    return b==0?a:gcd(b,a%b);
}
void exgcd(LL a,LL b,LL &d,LL &x,LL &y){
    if(b==0){
        x=1;y=0;d=a;
        return;
    }
    exgcd(b,a%b,d,y,x);
    y-=x*(a/b);
}
LL slove(void)//x=b[i](mod a[i])
{
    LL ta=a[0],tb=b[0];
    bool flag=true;
    for(int i=1;i<n;i++)
    {
        LL xa=ta,xb=a[i],c=b[i]-tb,d,x,y;
        exgcd(xa,xb,d,x,y);
        if(c%d)
        {
            flag=false;break;
        }
        LL tm=xb/d;
        x=(x*(c/d)%tm+tm)%tm;
        tb=ta*x+tb;
        ta=ta/d*a[i];
    }
    if(!flag)
        return -1;
    return tb;
}
int main(void){
    long long int m=75,temp,f[75];
    f[0] = 1;
    f[1] = 1;
    for(int i=2;i<m;i++){
        f[i] = f[i-1]+f[i-2];
    }
    cin>>n;
 for(int i=0;i<n;i++)
  scanf("%lld%lld", &a[i], &b[i]);
    long long int t = slove();
 if(t == -1)
        printf("Tankernb!\n");
 else{
        for(int i=0;i<m;i++)
            if(t == f[i]){
                printf("Lbnb!\n");
                return 0;
            }
        if(t == 0)
            printf("Lbnb!\n");
        else
         printf("Zgxnb!");
    }
    return 0;
}
