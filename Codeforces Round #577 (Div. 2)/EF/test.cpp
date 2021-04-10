#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1005;
int n, m;
int whitex, whitey, blackx, blacky;
int diswhitegoal[N][N];
int disblackgoal[N][N];
bool visitedwhite[N][N];
bool visitedblack[N][N];
int act=-1;
vector < pair < int, int > > positions;
vector < pair < int, int > > directions={{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
vector < pair < int, int > > movesfrom[N][N];
void legalmoves(int x, int y)
{
    for (auto s: directions)
    {
        if (1<=x+s.first && x+s.first<=n && 1<=y+s.second && y+s.second<=m)
        {
            movesfrom[x][y].push_back({x+s.first, y+s.second});
        }
    }
}
void bfswhite(int x, int y)
{
    for (auto s: movesfrom[x][y])
    {
        if (x<1 || y<1 || x>n || y>m) continue;
        if (!visitedwhite[s.first][s.second])
        {
        diswhitegoal[s.first][s.second]=1+diswhitegoal[x][y];
        visitedwhite[s.first][s.second]=true;
        positions.push_back({s.first, s.second});
        }
    }
    if (act+1<positions.size())
    {
        act++;
        bfswhite(positions[act].first, positions[act].second);
    }
}
void bfsblack(int x, int y)
{
    for (auto s: movesfrom[x][y])
    {
        if (!visitedblack[s.first][s.second])
        {
        disblackgoal[s.first][s.second]=1+disblackgoal[x][y];
        visitedblack[s.first][s.second]=true;
        positions.push_back({s.first, s.second});
        }
    }
    if (act+1<positions.size())
    {
        act++;
        bfsblack(positions[act].first, positions[act].second);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    cin>>whitex>>whitey>>blackx>>blacky;
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=m; j++)
        {
            legalmoves(i, j);
        }
    }
    visitedwhite[n/2][m/2]=true;
    act=-1;
    bfswhite(n/2, m/2);
    act=-1;
    positions={};
    visitedblack[(n/2)+1][m/2]=true;
    bfsblack(n/2+1, m/2);
    if (diswhitegoal[whitex][whitey]+1<=diswhitegoal[blackx][blacky] && diswhitegoal[whitex][whitey]<=disblackgoal[blackx][blacky])
    {
        cout<<"WHITE"<<endl;
        while (whitex!=n/2 || whitey!=m/2)
        {
            for (auto s: movesfrom[whitex][whitey])
            {
                if (diswhitegoal[s.first][s.second]<diswhitegoal[whitex][whitey])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    whitex=s.first;
                    whitey=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    if (whitex!=n/2 || whitey!=m/2) cin>>blackx>>blacky;
                    break;
                }
            }
        }
        return 0;
    }
    if (disblackgoal[blackx][blacky]+2<=disblackgoal[whitex][whitey] && disblackgoal[blackx][blacky]+1<=diswhitegoal[whitex][whitey])
    {
        cout<<"BLACK"<<endl;
        while (blackx!=n/2+1 || blacky!=m/2)
        {
            for (auto s: movesfrom[blackx][blacky])
            {
                if (disblackgoal[s.first][s.second]<disblackgoal[blackx][blacky])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    blackx=s.first;
                    blacky=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    if (blackx!=n/2+1 || blacky!=m/2) cin>>whitex>>whitey;
                    break;
                }
            }
        }
        return 0;
    }
    if ((whitex+whitey)%2!=(blackx+blacky)%2)
    {
        cout<<"WHITE"<<endl;
        if (diswhitegoal[whitex][whitey]<=disblackgoal[blackx][blacky])
        {
            while (whitex!=n/2 || whitey!=m/2)
        {
            for (auto s: movesfrom[whitex][whitey])
            {
                if (diswhitegoal[s.first][s.second]<diswhitegoal[whitex][whitey])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    whitex=s.first;
                    whitey=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    cin>>blackx>>blacky;
                    break;
                }
            }
        }
        }
        else{
        while (whitex!=n/2+1 || whitey!=m/2)
        {
            for (auto s: movesfrom[whitex][whitey])
            {
                if (disblackgoal[s.first][s.second]<disblackgoal[whitex][whitey])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    if (blackx==s.first && blacky==s.second)
                    {
                        return 0;
                    }
                    whitex=s.first;
                    whitey=s.second;
                    cin>>blackx>>blacky;
                    break;
                }
            }
        }
        for (auto s: movesfrom[whitex][whitey])
        {
            if (blackx==s.first && blacky==s.second)
            {
                cout<<s.first<<" "<<s.second<<endl;
                return 0;
            }
        }
        while (whitex!=n/2 || whitey!=m/2)
        {
            for (auto s: movesfrom[whitex][whitey])
            {
                if (diswhitegoal[s.first][s.second]<diswhitegoal[whitex][whitey])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    whitex=s.first;
                    whitey=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    if (whitex!=n/2 || whitey!=m/2) cin>>blackx>>blacky;
                    break;
                }
            }
        }
        }
        return 0;
    }
    else{
            cout<<"BLACK"<<endl;
            cin>>whitex>>whitey;
            if (diswhitegoal[whitex][whitey]>=disblackgoal[blackx][blacky])
        {
            while (blackx!=n/2+1 || blacky!=m/2)
        {
            for (auto s: movesfrom[blackx][blacky])
            {
                if (disblackgoal[s.first][s.second]<disblackgoal[blackx][blacky])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    blackx=s.first;
                    blacky=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    cin>>whitex>>whitey;
                    break;
                }
            }
        }
        }
        else{
        while (blackx!=n/2 || blacky!=m/2)
        {
            for (auto s: movesfrom[blackx][blacky])
            {
                if (diswhitegoal[s.first][s.second]<diswhitegoal[blackx][blacky])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    if (whitex==s.first && whitey==s.second)
                    {
                        return 0;
                    }
                    blackx=s.first;
                    blacky=s.second;
                    cin>>whitex>>whitey;
                    break;
                }
            }
        }
        for (auto s: movesfrom[blackx][blacky])
        {
            if (whitex==s.first && whitey==s.second)
            {
                cout<<s.first<<" "<<s.second<<endl;
                return 0;
            }
        }
        while (blackx!=n/2+1 || blacky!=m/2)
        {
            for (auto s: movesfrom[blackx][blacky])
            {
                if (disblackgoal[s.first][s.second]<disblackgoal[blackx][blacky])
                {
                    cout<<s.first<<" "<<s.second<<endl;
                    blackx=s.first;
                    blacky=s.second;
                    if (whitex==blackx && whitey==blacky) return 0;
                    if (blackx!=n/2+1 || blacky!=m/2) cin>>whitex>>whitey;
                    break;
                }
            }
        }
        }
        return 0;
    }
}
