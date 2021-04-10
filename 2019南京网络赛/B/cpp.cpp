#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int t;
long long phi[1000010];
long long p[1000010];
bool f[1000010];

const int pow2[] = {1, 2, 4, 16, 65536},
	p2[] = {1, 1, 4, 27, 256, 3125, 46656, 823543};

void prework() {
	long long n = 1000000;
	f[1]=1; phi[1]=1;
	for (int i=2;i<=n;++i) {
	    if (!f[i]) {
	        p[++t]=i; phi[i]=i-1;
		}
	    for (int j=1;j<=t;++j) {
	      	if (i*p[j]>n) break;
	      	f[i*p[j]]=1;
	        if (i%p[j]==0) {
	            phi[i*p[j]]=phi[i]*p[j];
	            break;
	        }
	        else
	          phi[i*p[j]]=phi[i]*(p[j]-1);
	    }
	}
}
long long my_power(long long a, long long b, long long m) {
	if (b == 0) return 1 % m;
	if (b == 1) return a % m;
	long long t = my_power(a, b/2, m);
	if (b % 2 == 0) return t * t % m;
	else return t * t % m * a % m;
}

long long gcd(long long a, long long b) {
	if(a < b) swap(a, b);
	long long c;
	while(b)
		c = a % b, a = b, b = c;
	return a;
}

long long calc(long long a, long long b, long long m) {
    if(a == 1)
        return 1 % m;
	if (b == 0) {
		return 1 % m;
	}
	if(b == 1)
		return a % m;
	if (m == 1) {
		return 0;
	}
	if(a == 2 && b <= 4)
		return pow2[b] % m;
	if(b == 2 && a <= 7)
		return p2[a] % m;
	long long rest;
	if(gcd(a, m) == 1)
		rest = calc(a, b - 1, phi[m]);
	else 
		rest = calc(a, b - 1, phi[m]) + phi[m];
	return my_power(a, rest, m);
}
int main() {
	long long a,b,m;
	prework();
	scanf("%d",&t);
	while (t--) {
		scanf("%lld%lld%lld", &a,&b,&m);
		printf("%lld\n",calc(a,b,m));
	}
}
