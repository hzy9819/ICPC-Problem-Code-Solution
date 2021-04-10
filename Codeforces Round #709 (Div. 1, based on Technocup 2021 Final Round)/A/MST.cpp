#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>

using namespace std;

const int N = 200200;

vector <int> canf[N];
vector <int> av[N];
vector <int> big;
vector <int> tmp;

int ans[N];
void init();

	int n, m;

	//n friend m day
void solve()
{
	cin >> n >> m;
	int up = (m+1)/2;
	for (int i = 1, x;i <= m; ++i)
	{
		cin >> x;
		canf[i].push_back(x);
		for (int j = 1; j<= canf[i][0]; ++j)
			cin >> x, av[x].push_back(i), canf[i].push_back(x);
	}
	
	for (int i = 1; i<=m; ++i)
		if(canf[i].empty() || canf[i][0] ==0)
		{
			puts("NO");
			return;
		}//cout<<"SDF"<<endl;
	for (int i= 1; i<= n;++i)
	{
		if(av[i].size()> up)
			big.push_back(i);
	}//cout<<"SDF"<<endl;
	if(big.empty())
	{
		puts("YES");
		for (int i =1; i< m; ++i)
			cout << canf[i][1]<<" ";
		cout << canf[m][1]<<endl;
		return;
	}
	int now = 0;
	bool flag = 0;
	for (int i = 0; i < big.size();++i)
	{
		int x = big[i];
		now = x;
		int sum = av[x].size();//cout << sum << "        asfdsaf" <<endl;
		tmp.clear();
		for (int j = 0; j< av[x].size();++j)
		{
		//	cout << av[x][j]<<" " <<canf[av[x][j]][0]<<"SDFDSFDSF"<<endl;
			if(canf[av[x][j]][0]> 1)
				tmp.push_back(av[x][j]), sum--;
			if(sum <= up)
			{
				flag = 1;
				goto lala;
			}
		}
	}//cout<<"SDF"<<endl;
lala:
	if(!flag)
		{
			puts("NO");return;
		}
	puts("YES");
	for (int i = 1;i <= m; ++i)
		ans[i] = 0;
	for (int i =0;i < tmp.size(); ++i)
		for (int j = 1; j <= canf[tmp[i]][0]; ++j)
			if(canf[tmp[i]][j]!=now)
			{
				ans[tmp[i]] = canf[tmp[i]][j];
				break;
			}
	for (int i = 0; i< av[now].size(); i++)
		if(ans[av[now][i]]==0)
			ans[av[now][i]] = now;
	for (int i = 1; i <= m;++i)
		if(!ans[i])
			ans[i] = canf[i][1];
	for (int i = 1;i <m; ++i)
		cout << ans[i] <<" ";
		cout << ans[m]<<endl;
}

void init()
{
	for (int i = 1;i <=n; ++i)
		av[i].clear();
	for (int i =1;i<=m;++i)
		canf[i].clear();
		big.clear();
}

int main()
{
	int T;
	cin >> T;
	while(T--)
		solve(), init();
}
