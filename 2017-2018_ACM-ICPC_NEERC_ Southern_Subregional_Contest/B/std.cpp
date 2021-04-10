#include<bits/stdc++.h>
#define mp make_pair
#define pii pair<int,int>
#define se second
#define fi first

using namespace std;
priority_queue<pii> h;
vector<int> g[200010],w[200010],s[200010];
int q[200010],d[200010],ans[200010],a[200010],v[200010],mi[200010],n,m,k,f,r;

void work(int x)
{
    for (int j=0; j<w[x].size(); j++)
    {
        int y=w[x][j];
        --d[y];
        if (d[y]==0&&!ans[y]) h.push(mp(mi[y],y));
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        ans[i]=a[i]; //ans[i] means the i-th not number
        s[a[i]].push_back(i); //s[i] save the not whose number is i
        v[a[i]]=1; //v[i] record if has some not's number is i
    }
    for (int i=1; i<=m; i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[y].push_back(x); //postive graph
        w[x].push_back(y); //negative graph
        d[x]++; //in degree
    }
    f=1,r=0;
    for (int i=1; i<=n; i++)
        if (!d[i]) 
        {
            q[++r]=i; //save the first not
            mi[i]=1; //mi[i] save the min number of i
        }
    while (f<=r)
    {
        int x=q[f++];
        if (a[x])
        {
            if (a[x]<mi[x])
            {
                puts("-1");
                return 0;
            }
            else mi[x]=a[x];
        }
        for (int i=0; i<g[x].size(); i++)
        {
            int y=g[x][i];
            mi[y]=max(mi[y],mi[x]+1);
            if (--d[y]==0) q[++r]=y;
        }
    } //top sort
    for (int i=1; i<=n; i++)
        d[i]=g[i].size();
    for (int i=1; i<=n; i++)
        if (!d[i]&&!ans[i])
        {
            h.push(mp(mi[i],i));
            //cout <<mi[i]<<" "<<i<<endl;
        }
    for (int i=k; i>=1; i--)
    {
        for (int j=0; j<s[i].size(); j++)
            work(s[i][j]);
        while (!h.empty())
        {
            int x=h.top().se;
           // cout <<x<<" "<<i<<" "<<mi[x]<<" "<<ans[x]<<endl;
            if (mi[x]>i)
            {
                puts("-1");
                return 0;
            }
            if (mi[x]==i)
            {
                ans[x]=i; v[i]=1;
                work(x);
                h.pop();
            }
            else break;
        }
        if (!v[i])
        {
            if (!h.empty())
            {
                int x=h.top().se;
                ans[x]=i;
                work(x);
                h.pop();
            }
            else {
                puts("-1");
                return 0;
            }
        }
    }
    for (int i=1; i<=n; i++)
        for (int j=0; j<g[i].size(); j++)
            if (ans[i]>=ans[g[i][j]])
            {
                puts("-1");
                return 0;
            }

    for (int i=1; i<=n; i++)
    {
        printf("%d",ans[i]);
        if (i!=n) printf(" "); else puts("");
    }
}
