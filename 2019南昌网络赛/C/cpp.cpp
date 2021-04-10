#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define min(a, b) ((a) < (b) ? (a) : (b)) 
#define nn 200002
using namespace std;

struct query{
	int l,r,o;
}Q[nn];
int n,q,ans[nn];
char s[nn];
int f[nn][5][4],rr[nn],rres[nn];
vector<query> v[nn];

int read() {
	int w = 0, f = 0; char c = getchar();
	while((c < '0' || c > '9') && c != '-') c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

void work(int l,int* R,int* res,int rlen)
{
	int cur=0;
	memset(f[cur],0x7f,sizeof(f[cur]));
	f[cur][0][0]=0;
	int rmax=R[rlen-1];
	int rtop=0;
	int td,t8d,t9d;
	for(int i=l;i<=rmax;++i)
	{
		cur^=1;
		memset(f[cur],0x7f,sizeof(f[cur]));
		if(s[i]=='9')
		{
			for(int t9=0;t9<=4;++t9)
				for(int t8=0;t8<=3;++t8)
				{
					if(t9==0)
					{
						f[cur][t9+1][t8]=min(f[cur][t9+1][t8],f[cur^1][t9][t8]);
						f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]+1);
					}
					else f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]);
				}
		}
		else if(s[i]=='8')
		{
			for(int t9=0;t9<=4;++t9)
				for(int t8=0;t8<=3;++t8)
				{
					if(t8==0)
					{
						f[cur][t9][t8+1]=min(f[cur][t9][t8+1],f[cur^1][t9][t8]);
						f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]+1);
					}
					else f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]);
				}						
		}
		else if(s[i]=='1'||s[i]=='0')
		{
			if(s[i]=='1') td=1;else td=2;
			for(int t9=0;t9<=4;++t9)
				for(int t8=0;t8<=3;++t8)
				{
					if(t8==td) t8d=1;else t8d=0;
					if(t9==td) t9d=1;else t9d=0;
					f[cur][t9+t9d][t8+t8d]=min(f[cur][t9+t9d][t8+t8d],f[cur^1][t9][t8]);
					f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]+1);
				}												
		}
		else if(s[i]=='2')
		{
			for(int t9=0;t9<=4;++t9)
				for(int t8=0;t8<=3;++t8)
				{
					if(t9==3) t9d=1;else t9d=0;
					if(t8<3) f[cur][t9+t9d][t8]=min(f[cur][t9+t9d][t8],f[cur^1][t9][t8]);
					f[cur][t9][t8]=min(f[cur][t9][t8],f[cur^1][t9][t8]+1);
				}																		
		}
		else
		{
			for(int t9=0;t9<=4;++t9)
				for(int t8=0;t8<=3;++t8)
					f[cur][t9][t8]=f[cur^1][t9][t8];
		}
		if(i==R[rtop])
		{
			int ans=1e9;
			for(int t8=0;t8<=3;++t8) ans=min(ans,f[cur][4][t8]);
			if(ans>=1e9) ans=-1;
			res[rtop]=ans;
			rtop++;
		}
	}
}

inline bool comp(const query & _, const query & __)
{
	return _.l==__.l?_.r<__.r:_.l<__.l;
}

int main()
{
	int l,r;
	n = read(), q = read();
	scanf("%s\n",s);
	for(int i=1;i<=q;++i)
	{
		l = read(), r = read();
		l--; r--;
		Q[i].l=l,Q[i].r=r,Q[i].o=i;
	}
	sort(Q+1,Q+q+1,comp);
	for(int i=1;i<=q;++i) v[Q[i].l].push_back(Q[i]);
	int dep=0,tmp=0;
	for(int i=0;i<n;++i)
	{
		dep=0;
		for(auto q_:v[i]) l=q_.l,rr[dep++]=q_.r;
		work(l,rr,rres,dep);
		tmp=0;
		for(auto q_:v[i]) ans[q_.o]=rres[tmp++];
	}
	for(int i=1;i<=q;++i) printf("%d\n",ans[i]);

	return 0;
}
