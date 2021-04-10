#include<bits/stdc++.h>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;
const int MAX = 4e3 + 10;
const int MOD = 1e9 + 7;
typedef long long ll;
vector <int> e[MAX];
int siz[MAX], d[MAX];
void DFS(int k, int fa)
{
    siz[k] = 1;
    d[k] = 0;
    for(size_t i = 0; i < e[k].size(); i++)
    {
        if(e[k][i] == fa)continue;
        DFS(e[k][i] , k);
        siz[k] += siz[e[k][i]];
        d[k] = max(d[k], siz[e[k][i]]);
    }
}
void getroot(int k, int fa, int p, pair<int,int> & root)
{
    d[k] = max(p - siz[k], d[k]);
    if(root.first == 0 || d[k] < d[root.first]) root.first = k;
    else if(root.first != 0 && d[k] == d[root.first]) root.second = k;
    for(size_t i=0;i<e[k].size();i++)
    {
        if(e[k][i]==fa)continue;
        getroot(e[k][i],k,p,root);
    }
}
string dfs(int k,int fa,int T)
{
    if(k==0)return "";
    vector<string>Q;
    for(size_t i=0;i<e[k].size();i++)
    {
        int nex=e[k][i];
        if(nex==fa||nex==T)continue;
        Q.push_back(dfs(nex,k,T));
    }
    string ans="0";
    sort(Q.begin(),Q.end());
    for(size_t i=0;i<Q.size();i++)ans+=Q[i];
    ans+="1";
    return ans;
}
 
int cut(int k)
{
    if(e[k].size()<2)return -1;
    string A,B;
    for(size_t i=0;i<e[k].size();i++)
    {
        pair<int,int> root = make_pair(0, 0);
        DFS(e[k][i],k);
        getroot(e[k][i],k,siz[e[k][i]],root);
        if(i==0)
        {
            A=dfs(root.first,0,k);
            B=dfs(root.second,0,k);
        }
        if(A!=dfs(root.first,0,k)&&A!=dfs(root.second,0,k))A="";
        if(B!=dfs(root.first,0,k)&&B!=dfs(root.second,0,k))B="";
        if(A==""&&B=="")return -1;
    }
    return (int)e[k].size();
}
int main() {
    int n;
    cin >> n;
    for(int i = 1;i < n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    pair<int,int> root = make_pair(0, 0);
    DFS(1, 0);
    getroot(1, 0, n, root);
    cout << max(cut(root.first), cut(root.second)) << endl;
    return 0;
}
