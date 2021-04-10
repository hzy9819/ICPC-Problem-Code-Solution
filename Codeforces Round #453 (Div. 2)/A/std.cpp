#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
const int N=100051;
int n,m;
int a[N],b[N];
int l,r;
void solve()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
    scanf("%d%d",&a[i],&b[i]);
  r=0;
  for(int i=1;i<=n;i++)
    if(a[i]<=r)
      r=max(r,b[i]);
  if(r!=m)printf("NO\n");
  else printf("YES\n");
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
