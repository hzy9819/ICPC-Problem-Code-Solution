#include <cstdio>
const int maxn = 1e5 + 10;
int gcd(int a,int b){
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
struct Node{
	int u,v;
}p[maxn];
int main(){
    int n,m,k=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n&&k<m;i++){
        for(int j=i+1;j<=n&&k<m;j++){
            if(gcd(i,j)==1){
                p[k].u=i;
				p[k].v=j;
				k++;
            }
        }
    }
    if(m<n-1||k<m){
    	puts("Impossible");
    }
	else{
		puts("Possible");
		for(int i=0;i<k;i++){
			printf("%d %d\n",p[i].u,p[i].v);
		}
    }
    return 0;
}
