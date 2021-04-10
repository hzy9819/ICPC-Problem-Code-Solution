#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=300051;
int n;
int h[N];
vector<int> dep[N];
int fa1[N],fa2[N];
void solve()
{
  scanf("%d",&n);
  for(int i=1;i<=n+1;i++)
    scanf("%d",&h[i]);
  dep[1].push_back(1);
  fa1[1]=0;
  int tot=1,last=1;
  for(int i=2;i<=n+1;i++)
  {
    for(int j=1;j<=h[i];j++)
    {
      dep[i].push_back(++tot);
      fa1[tot]=last;
    }
    last=tot;
  }
  for(int i=1;i<=tot;i++)
  fa2[i]=fa1[i];
  int flag=0;
  for(int i=n+1;i>=2;i--)
  {
    if(h[i]>1&&h[i-1]>1)
    {fa2[dep[i][0]]=dep[i-1][0];flag=1;break;}
  }
  if(flag==0)
    printf("perfect\n");
  else
  {
    printf("ambiguous\n");
    for(int i=1;i<=tot;i++)
      printf("%d ",fa1[i]);
    printf("\n");
    for(int i=1;i<=tot;i++)
      printf("%d ",fa2[i]);
    printf("\n");
  }
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
