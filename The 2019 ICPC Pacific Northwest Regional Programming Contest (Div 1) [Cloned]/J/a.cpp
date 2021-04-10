#include <bits/stdc++.h>
#define LL long long
using namespace std;

int read() {
	int f = 0, w = 0; char c = getchar();
	while((c != '-') && (c < '0' || c > '9'))
		c = getchar();
	if(c == '-')
		f = 1, c = getchar();
	while(c >= '0' && c <= '9')
		w = w * 10 + c - '0', c = getchar();
	return f ? -w : w;
}

const int N = 1e5+100;
const double pi = acos(-1);
int m, n;
double T[N], s[N], a[N], b[N];

struct Node
{
	double a, b;
	double ang;
	operator < (const Node &x)
	{
		return ang < x.ang;
	}
}p[N*10];

double A,B;
Node t[10];

double getdis(double ang, int k)
{
	double mn[3];
			mn[0]= min(min(fabs(ang - a[k]), fabs(ang - a[k] - 2*pi)), fabs(ang - a[k] + 2*pi));
			mn[1]= min(min(fabs(ang - b[k]), fabs(ang - b[k] - 2*pi)), fabs(ang - b[k] + 2*pi));
			mn[2] = min(mn[0], mn[1]);
	return mn[2];
}

void gugu(int k)
{
	if(s[k] == 0)
		return;
	t[0].ang = 0;
	b[k] = pi+a[k];
	if (b[k] >= 2*pi)
		b[k] -= 2*pi;;
	int M;
	if (a[k] == 0)
	{
		M = 3;
		for (int i =1;i <= 3;++i)
			t[i].ang = t[i-1].ang+pi/2;
	}
	else
	{
		M = 4;
		t[1].ang = a[k];
		for (int i = 2;i <= 4;++i)
		{
			t[i].ang = t[i-1].ang + pi/2;
			if (t[i].ang >= 2*pi)
				t[i].ang -= 2*pi;
		}
		sort(t+1, t+5);		
	}
	for (int i = 0 ;i <= M; ++i)
	{
		double ang = t[i].ang + 1e-7;
		double bb;
		if ((bb = getdis(t[i].ang, k)) < getdis(ang, k))
		{
			t[i].a = s[k];
		}
		else
		{
			t[i].a = -s[k];
		}
		t[i].b = bb - t[i].a * t[i].ang;
		printf("%lf %lf %lf \n", bb, t[i].ang, t[i].b);
	}
	int tt = M;
	for (int i = 0 ;i < tt; ++i)
	{
		if (t[i].a > 0 && t[i].a*t[i].ang+t[i].b > T[k])
		{
			t[i].a = 0, t[i]. b = T[k];
			continue;
		}
		if (t[i].a < 0 && t[i].a *t[i+1].ang + t[i].b > T[k])
		{
			t[i].a = 0, t[i]. b = T[k];
			continue;
		}
		if(t[i].a*t[i].ang+t[i].b > T[k])
		{
			double ang = (T[k] - t[i].b) / t[i].a;
			t[++M].a = t[i].a;
			t[M].b = t[i].b;
			t[M].ang = ang;
			t[i].a = 0;
			t[i].b = T[k];
		}
		else if (t[i].a *t[i+1].ang + t[i].b > T[k])
		{
			double ang = (T[k] - t[i].b) / t[i].a;
			t[++M].a = 0;
			t[M].b = T[k];
			t[M].ang = ang;
		}
	}
	if (t[tt].a > 0 && t[tt].a*t[tt].ang+t[tt].b > T[k])
	{
		t[tt].a = 0, t[tt]. b = T[k];
	}
	else if (t[tt].a < 0 && t[tt].a *2*pi+ t[tt].b > T[k])
	{
		t[tt].a = 0, t[tt]. b = T[k];
	}
	else if(t[tt].a*t[tt].ang+t[tt].b > T[k])
	{
		double ang = (T[k] - t[tt].b) / t[tt].a;
		t[++M].a = t[tt].a;
		t[M].b = t[tt].b;
		t[M].ang = ang;
		t[tt].a = 0;
		t[tt].b = T[k];
	}
	else if (t[tt].a *2*pi+ t[tt].b > T[k])
	{
		double ang = (T[k] - t[tt].b) / t[tt].a;
		t[++M].a = 0;
		t[M].b = T[k];
		t[M].ang = ang;
	}
	sort(t+1, t+M+1);
	for (int i =0 ;i <=M; ++i)
		printf("%lf %lf %lf\n", t[i].ang, t[i].a, t[i]. b); 
	for (int i = M; i; --i)
		t[i].a-=t[i-1].a, t[i].b -= t[i-1].b;
	for (int i = 1; i <= M; ++i)
		p[m+i] = t[i];
	m= M+m;
	A += t[0].a, B+= t[0].b;
}

int main()
{
	n  = read();
	double ang = 0;
	m = 0;A = B =0;
	for (int i = 1;i <= n; ++i)
	{
		scanf("%lf%lf%lf", &T[i], &s[i], &a[i]);
		gugu(i);
	}
	double ans = B;
	sort(p+1, p +1+m);
	for(int i = 1;i <= m; ++i)
	{
		ang = p[i].ang;
		ans = min(ans, ang*A + B);
		A+=p[i].a, B+=p[i].b;
		ans = min(ans, ang*A + B);
	}
	ans = -ans;
	for(int i =1 ;i <=n; ++i)
		ans += T[i];
	printf("%.8lf\n", ans);
}
