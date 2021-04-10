#include<bits/stdc++.h>
using namespace std;
//
int n;
long long L[2000004];
vector<long long> v[2000002],sum[2000002];
void dfs(int node){
	if( (node<<1) <= n ) dfs(node<<1);
	if( (node<<1|1) <= n ) dfs(node<<1|1);
	v[node].resize(v[node<<1].size()+v[node<<1|1].size()+1);
	sum[node].resize(v[node].size());
	sum[node][0]=v[node][0]=L[node];
	merge(v[node<<1].begin(),v[node<<1].end(),v[node<<1|1].begin(),v[node<<1|1].end(),v[node].begin()+1);
	for(int i=1;i<v[node].size();i++) sum[node][i]=v[node][i]+sum[node][i-1];
}
int main(){
	freopen("D.in", "r", stdin), freopen("std.out", "w", stdout);
	int m;
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		scanf("%lld",&L[i]);
		L[i]+=L[i/2];
	}
	dfs(1);
	while(m--){
		int node,curr_node,last_node,tot;
		long long ans=0,h;
		scanf("%d%lld",&node,&h);
		curr_node=node,last_node=-1;
		while(curr_node>=1){
			if(h-(L[node]-L[curr_node])<0) break;
            if(last_node==-1){
				tot = upper_bound(v[node].begin(),v[node].end(),L[node]+h)-v[node].begin();
                ans+=(tot) ? tot*(L[node]+h)-sum[node][tot-1] : 0;
			}else{
				last_node^=1;
                tot=upper_bound(v[last_node].begin(),v[last_node].end(),L[last_node]+h-(L[node]+L[last_node]-2*L[curr_node]))-v[last_node].begin();
                ans+= h-(L[node]-L[curr_node])+( tot ? (tot*(L[last_node]+h-(L[node]+L[last_node]-2*L[curr_node]))-sum[last_node][tot-1] ) : 0 );
			}
            
			last_node=curr_node;
			curr_node/=2;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
