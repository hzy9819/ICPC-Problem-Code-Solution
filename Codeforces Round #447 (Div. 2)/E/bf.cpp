#include <math.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int N,M,S,TE,TD,TT=0,TP=0,TC=0,FT=0,LT=0,stE[1111111],stD[1111111],dfn[1111111],las[1111111],stk[1111111],bel[1111111],ind[1111111],que[1111111];
long long sum[1111111],ans[1111111];
bool flg[1111111],vis[1111111];
struct edge{
	   int adj,nex;
	   long long wei;
	   edge (int a_=0,int n_=0,long long w_=0){
			adj=a_;
			nex=n_;
			wei=w_;
	   }
	   long long val(){
	   		long long k=(long long)(sqrtl((long double)wei*2+0.25)-0.5);
	   		return (k*(6*wei-(k+1)*(k+2)))/6+wei;
	   }
}E[1111111],D[1111111];
void addE(int u,int v,int w){
	 E[++TE]=edge(v,stE[u],w);
	 stE[u]=TE;
}
void addD(int u,int v,long long w){
	 ind[v]++;
	 D[++TD]=edge(v,stD[u],w);
	 stD[u]=TD;
}
void tarjan(int x){
	 stk[++TP]=x;
	 flg[x]=true;
	 dfn[x]=las[x]=++TT;
	 for (int i=stE[x];i;i=E[i].nex){
		 if (!dfn[E[i].adj]){
			tarjan(E[i].adj);
			las[x]=min(las[x],las[E[i].adj]);
		 }
		 else{
			  if (flg[E[i].adj]){
			  	 las[x]=min(las[x],las[E[i].adj]);
			  }
		 }
	 }
	 if (las[x]==dfn[x]){
		TC++;
		do{
		   bel[stk[TP]]=TC;
		   flg[stk[TP]]=false;
		}while(stk[TP--]!=x);
	 }
}
void dfs(int x){
	 vis[x]=true;
	 for (int i=stD[x];i;i=D[i].nex){
		 if (!vis[D[i].adj]){
			dfs(D[i].adj);
		 }
	 }
}
int main(){
	freopen("E.in", "r", stdin), freopen("std.out", "w", stdout);
	int p,u,v,w;
	long long Ans=0;
	scanf("%d%d",&N,&M);
	for (int i=1;i<=M;i++){
		scanf("%d%d%d",&u,&v,&w);
		addE(u,v,w);
	}
	for (int i=1;i<=N;i++){
		if (!dfn[i]){
		   tarjan(i);
		}
	}
	for (int i=1;i<=N;i++){
		for (int j=stE[i];j;j=E[j].nex){
			if (bel[i]==bel[E[j].adj]){
			   sum[bel[i]]+=E[j].val();
			}
		}
	}
	for (int i=1;i<=N;i++){
		for (int j=stE[i];j;j=E[j].nex){
			if (bel[i]!=bel[E[j].adj]){
			   addD(bel[i],bel[E[j].adj],E[j].wei+sum[bel[E[j].adj]]);
			}
		}
	}
	scanf("%d",&S);
	S=bel[S];
	dfs(S);
	for (int i=1;i<=TC;i++){
		if (!vis[i]){
		   for (int j=stD[i];j;j=D[j].nex){
			   ind[D[j].adj]--;
		   }
		}
	}
	que[++FT]=S;
	ans[S]=sum[S];
	while (LT!=FT){
		  p=que[++LT];
		  Ans=max(Ans,ans[p]);
		  for (int i=stD[p];i;i=D[i].nex){
			  ans[D[i].adj]=max(ans[D[i].adj],ans[p]+D[i].wei);
			  ind[D[i].adj]--;
			  if (!ind[D[i].adj]){
			  	 que[++FT]=D[i].adj;
			  }
		  }
	}
	printf("%lld",Ans);
	return 0;
}
