#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N,K;
ll Count(ll x)
{
    ll ans=0;
    while(x)
    {
        x-=(x&-x);
        ans++;
    }
    return ans;
}
ll tool[100];



int main()
{
	freopen("B.in", "r", stdin), freopen("B.out", "w", stdout);
    cin>>N>>K;
    if(Count(N)>K)
    {puts("No");return 0;}
    puts("Yes");
    ll i;
    ll tot=0;
    for(i=0;i<63;i++)
        if((1ll<<i)&N)
        {tool[i+20]=1;tot++;}
    i=100;
    while(1)
    {
        i--;
        if(tool[i]==0) continue;
        ll now=tool[i]+tot;
        if(now>K)break;
        tot=now;
        tool[i-1]+=tool[i]<<1;
        tool[i]=0;
    }
    for(i=0;i<100;i++) if(tool[i]) break;
    ll j=i-20;
    tool[i]--;


    for(i=99;i>=0;i--)
    {
        while(tool[i]--) printf("%lld ",i-20);
    }
    if(tot==K) printf("%lld ",j);
    else
    {
        ll p=K-tot;
        for(i=1;i<p;i++) printf("%lld ",j-i);
        printf("%lld %lld ",j-p,j-p);
    }


    return 0;
}
