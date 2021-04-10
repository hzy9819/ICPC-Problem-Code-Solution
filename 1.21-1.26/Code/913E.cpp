#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;

int n,vis[256][3];
string res[256][3];

int comp(string _, string __)
{
	return _.length()==__.length()?_<__:_.length()<__.length();
}

void upd(int& v, string& x, string y)
{
	if(!v)
	{
		v=1, x=y;
		return;
	}
	if(v==2) return;
	if(comp(y,x)) x=y;
}

int main()
{
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);

	res[15][2]="x", res[51][2]="y", res[85][2]="z";
	vis[15][2]=vis[51][2]=vis[85][2]=1;
	string t="";
	int ki,pi;
	for(int i=0;i<=255;++i)
		for(int j=0;j<=2;++j)
		{
			ki=-1,pi=-1;
			//cout<<i<<" "<<j<<" "<<res[7][0]<<" "<<res[7][1]<<" "<<res[7][2]<<endl;
			
			for(int k=0;k<=255;++k)
				for(int p=0;p<=2;++p)
				{
					if(vis[k][p]!=1) continue;
					if(ki<0||comp(res[k][p],t))
					{
						t=res[k][p];
						ki=k, pi=p;
					}
				}
			vis[ki][pi]=2;
			if(pi==0) upd(vis[ki][2],res[ki][2],'('+res[ki][0]+')');
			if(pi==1) upd(vis[ki][0],res[ki][0],res[ki][1]);
			if(pi==2)
			{
				upd(vis[ki][1],res[ki][1],res[ki][2]);
				upd(vis[ki^255][2],res[ki^255][2],'!'+res[ki][2]);
			}
			if(pi<=1)
			{
				for(int k=0;k<=255;++k)
				{
					if(!vis[k][pi+1]) continue;
					if(!pi) upd(vis[ki|k][pi],res[ki|k][pi],res[ki][pi]+'|'+res[k][pi+1]);
					else upd(vis[ki&k][pi],res[ki&k][pi],res[ki][pi]+'&'+res[k][pi+1]);
				}
			}
			if(pi>=1)
			{
				for(int k=0;k<=255;++k)
				{
					if(!vis[k][pi-1]) continue;
					if(pi==1) upd(vis[ki|k][pi-1],res[ki|k][pi-1],res[k][pi-1]+'|'+res[ki][pi]);
					else upd(vis[ki&k][pi-1],res[ki&k][pi-1],res[k][pi-1]+'&'+res[ki][pi]);
				}
			}
			
		}

	int x,m;
	scanf("%d\n",&n);
	for(int i=1;i<=n;++i)
	{
		m=0;
		for(int j=0;j<8;++j) scanf("%1d",&x),m=(m<<1)|x;
		scanf("\n");
		t=res[m][0];
		if(comp(res[m][1],t)) t=res[m][1];
		if(comp(res[m][2],t)) t=res[m][2];
		cout<<t<<"\n";
	}	
	
	return 0;
}
