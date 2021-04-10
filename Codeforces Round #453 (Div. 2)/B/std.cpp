#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=100051;
int n;
int a[N],b[N];
int l,r;
vector<int> add[N];
int col[N],bcol[N];
int tot=0;
void dfs(int x,int lc)
{
  if(lc!=col[x])
  {
    tot++;
    bcol[x]=col[x];
    lc=col[x];
  }
  else
    bcol[x]=lc;
  for(int i=0;i<add[x].size();i++)
    dfs(add[x][i],lc);
}
void solve()
{
  scanf("%d",&n);
  for(int i=2;i<=n;i++)
  {
    int x;
    scanf("%d",&x);
    add[x].push_back(i);
  }
  for(int i=1;i<=n;i++)
    scanf("%d",&col[i]);
  dfs(1,0);
  printf("%d\n",tot);
}
int main()
{
  int T;
  T=1;
  while(T--)
  {
    solve();
  }
  return 0;
}
