#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define LL long long
#define db double
#define Hzy(o) freopen(o".in", "r", stdin), freopen(o".out", "w", stdout)
using namespace std;

int read() {
	int w = 0, f = 0; char c = getchar();
	while(c != '-' && (c < '0' || c > '9')) c = getchar();
	if(c == '-') f = 1, c = getchar();
	while(c >= '0' && c <= '9') w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

const int N = 40;
const int P = 4;
const int PP = 3;

double f[N][N][N][N][4][3];
bool book[N][N][N][N][4][3];
// statu i,j,k,p q turn u posibility

double dfs(int i, int j, int k, int p, int q, int u)
{
	if(book[i][j][k][p][q][u])
		return f[i][j][k][p][q][u];

	int r = (q + 1) % P;
	db op[4] = {-1, -1, -1, -1};
	int num = 0;
	bool flag = 0;

	switch(q)
	{
		case 0:
			if(!i)
				return dfs(i, j, k, p, r, u);
		case 1:
			// choose k or p to minus
			// maximum 0

			if(!j)
				return dfs(i, j, k, p, r, u);	
			if(k)
				op[1] = dfs(i, j, k-1, p, r, 0);
			if(p)
				op[2] = dfs(i, j, k, p-1, r, 0);
			if(num == 1)
				f[i][j][k][p][q][u] = (op[1] == -1 ? dfs(i, j, k, p-1, r, u)\
									   : dfs(i, j, k-1, p, r, u));
			else if(op[1] < op[2])
				f[i][j][k][p][q][u] = dfs(i, j, k, p-1, r, u);
			else if(op[1] > op[2])
				f[i][j][k][p][q][u] = dfs(i, j, k-1, p, r, u);
			else
				f[i][j][k][p][q][u] = (dfs(i, j, k-1, p, r, u) +\
									   dfs(i, j, k, p-1, r, u)) / 2.0;
			break;
			
		case 2:
			// choose i or j or p to minus
			// maximum 1
			
			if(!k)
				return dfs(i, j, k, p, r, u);
			if(i)
				op[1] = dfs(i-1, j, k, p, r, 1);
			if(j)
				op[2] = dfs(i, j-1, k, p, r, 1);
			if(p)
				op[3] = dfs(i, j, k, p-1, r, 1);
			
			db tmp = max(max(op[1],op[2]),op[3]);
			num = 0;
			for(int lala = 1; lala <= 3; ++lala)
				if(op[lala] == tmp)
					num++;

			if(num == 1)
			{
				if(op[1] == tmp)
					f[i][j][k][p][q][u] = dfs(i-1, j, k, p, r, u);
				if(op[2] == tmp)
					f[i][j][k][p][q][u] = dfs(i, j-1, k, p, r, u);
				if(op[3] == tmp)
					f[i][j][k][p][q][u] = dfs(i, j, k, p-1, r, u);
			}
			else if(num == 2)
			{
				if(op[3] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j-1, k, p, r, u) + \
								   dfs(i-1, j, k, p, r, u)) / 2.0;
				if(op[1] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j-1, k, p, r, u) + \
								   dfs(i, j, k, p-1, r, u)) / 2.0;
				if(op[2] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j, k, p-1, r, u) + \
								   dfs(i-1, j, k, p, r, u)) / 2.0;
			}
			else
				f[i][j][k][p][q][u] = (dfs(i, j, k, p-1, r, u) + \
								   dfs(i-1, j, k, p, r, u) + \
									   dfs(i, j-1,k, p, r, u)) / 3.0;
			
			break;
			
		case 3:
			// choose i or j or k to minus
			// maximum 2

			if(!p)
				return dfs(i, j, k, p, r, u);
			if(i)
				op[1] = dfs(i-1, j, k, p, r, 2);
			if(j)
				op[2] = dfs(i, j-1, k, p, r, 2);
			if(k)
				op[3] = dfs(i, j, k-1, p, r, 2);
			
			db tmp = max(max(op[1],op[2]),op[3]);
			num = 0;
			for(int lala = 1; lala <= 3; ++lala)
				if(op[lala] == tmp)
					num++;

			if(num == 1)
			{
				if(op[1] == tmp)
					f[i][j][k][p][q][u] = dfs(i-1, j, k, p, r, u);
				if(op[2] == tmp)
					f[i][j][k][p][q][u] = dfs(i, j-1, k, p, r, u);
				if(op[3] == tmp)
					f[i][j][k][p][q][u] = dfs(i, j, k-1, p, r, u);
			}
			else if(num == 2)
			{
				if(op[3] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j-1, k, p, r, u) + \
								   dfs(i-1, j, k, p, r, u)) / 2.0;
				if(op[1] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j-1, k, p, r, u) + \
								   dfs(i, j, k-1, p, r, u)) / 2.0;
				if(op[2] != tmp)
					f[i][j][k][p][q][u] = (dfs(i, j, k-1, p, r, u) + \
								   dfs(i-1, j, k, p, r, u)) / 2.0;
			}
			else
				f[i][j][k][p][q][u] = (dfs(i, j, k-1, p, r, u) + \
								   dfs(i-1, j, k, p, r, u) + \
									   dfs(i, j-1,k, p, r, u)) / 3.0;
			break;
	}

//	cout<<i<<" "<<j<<" "<<k<<" "<<p<<" "<<q<<" "<<u<<endl<<f[i][j][k][p][q][u]<<"  SDF"<<endl;

	book[i][j][k][p][q][u] = 1;
	return f[i][j][k][p][q][u];
}

void solve()
{
	int i = read(), j = read(), k = read(), p = read();
	printf("%.6lf %.6lf %.6lf\n", dfs(i, j, k, p, 0, 0), \
		   dfs(i, j, k, p, 0, 1), dfs(i, j, k, p, 0, 2));
}

void initial()
{
	int i, j, k;
	for(i = 1; i < N; ++i)
		for(j = 0; j < N; ++j)
			for(k = 0; k < P; ++k)
			{
				book[i][j][0][0][k][0] = 1;
				f[i][j][0][0][k][0] = 1;
				
				book[i][j][0][0][k][1] = 1;
				f[i][j][0][0][k][1] = 0;

				book[i][j][0][0][k][2] = 1;
				f[i][j][0][0][k][2] = 0;
			}
	for(i = 1; i < N; ++i)
		for(j = 0; j < P; ++j)
		{
			book[0][0][0][i][j][2] = 1;
			f[0][0][0][i][j][2] = 1;
			
			book[0][0][0][i][j][0] = 1;
			f[0][0][0][i][j][0] = 0;

			book[0][0][0][i][j][1] = 1;
			f[0][0][0][i][j][1] = 0;
		}
	for(i = 1; i < N; ++i)
		for(j = 0; j < N; ++j)
			for(k = 0; k < P; ++k)
			{
				book[0][i][j][0][k][1] = 1;
				f[0][i][j][0][k][1] = 1;
				
				book[0][i][j][0][k][0] = 1;
				f[0][i][j][0][k][0] = 0;

				book[0][i][j][0][k][2] = 1;
				f[0][i][j][0][k][2] = 0;
			}
	for(i = 0; i < N; ++i)
		for(j = 1; j < N; ++j)
			for(k = 0; k < P; ++k)
			{
				book[0][i][j][0][k][1] = 1;
				f[0][i][j][0][k][1] = 1;
				
				book[0][i][j][0][k][0] = 1;
				f[0][i][j][0][k][0] = 0;

				book[0][i][j][0][k][2] = 1;
				f[0][i][j][0][k][2] = 0;
			}
}

int main()
{
//	freopen("data.in","r",stdin);
	initial();
	int T = read();
	while(T--)
		solve();
	return 0;
}
