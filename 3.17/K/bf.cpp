#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<map>
#include<math.h>
#include<queue>
#include<string>
using namespace std;
#define L long long
const L maxn = 200050 ;
const L INF = 999999999999999999 ;
/**
做一个三维的kdtree 进行最近距离的查找 同时记录最近的ans和最近的编号 随时进行对比
getdis函数 如果小于等于z 距离加上0 否则加上INF
*/
 
L n , m , cmp_d , root ;
struct node {
    L l , r ;
    L d[3] , Max[3] , Min[3] ;
    L c ;
    L id ;
}a[maxn];
bool cmp(node a , node b ){
    return a.d[cmp_d] < b.d[cmp_d] ;
}
void up(L p , L k ) {
    for(L i = 0; i < 3 ; i ++ ){
        a[p].Min[i] = min(a[p].Min[i] , a[k].Min[i]) ;
        a[p].Max[i] = max(a[p].Max[i] , a[k].Max[i]) ;
    }
}
L build(L l, L r , L D) {
    cmp_d = D ;
    L mid = (l+r)/2 ;
    nth_element(a+1+l,a+1+mid,a+1+r,cmp) ;
    for(L i = 0 ;i < 3 ; i ++) a[mid].Min[i] = a[mid].Max[i] = a[mid].d[i] ;
    if(l != mid) a[mid].l = build(l,mid-1,(D+1)%3) ; else a[mid].l = 0 ;
    if(r != mid) a[mid].r = build(mid+1,r,(D+1)%3) ; else a[mid].r = 0 ;
    if(a[mid].r)up(mid,a[mid].r);
    if(a[mid].l)up(mid,a[mid].l);
    return mid ;
}
L x,y,z;
L jl , ans ;
L getdis(L p) {
    L res = 0 ;
    if(z < a[p].Min[2]) return INF + 1 ;
    if(x > a[p].Max[0]) res += (x - a[p].Max[0]) * (x - a[p].Max[0]) ;
    if(x < a[p].Min[0]) res += (a[p].Min[0] - x) * (a[p].Min[0] - x) ;
    if(y > a[p].Max[1]) res += (y - a[p].Max[1]) * (y - a[p].Max[1]) ;
    if(y < a[p].Min[1]) res += (a[p].Min[1] - y) * (a[p].Min[1] - y) ;
    return res ;
}
void ask(L p) {
    L d0 = 0 ;
    L dl , dr ;
    if(a[p].d[2] > z)d0 += INF ;
    if(d0 == 0) {
        d0 += ((a[p].d[0]) - x) * ((a[p].d[0]) - x ) + ((a[p].d[1]) - y) * ((a[p].d[1]) - y )  ;
        if(d0 < jl){
            ans = p ;
            jl = d0 ;
        }
        else if(d0 == jl) {
            if(a[p].id < a[ans].id) {
                ans = p;
            }
        }
    }
    if(a[p].l)dl = getdis(a[p].l) ; else dl = INF + 1 ;
    if(a[p].r)dr = getdis(a[p].r) ; else dr = INF + 1 ;
    if(dl < dr ) {
        if(dl <= jl) ask(a[p].l) ;
        if(dr <= jl) ask(a[p].r) ;
    }
    else {
        if(dr <= jl) ask(a[p].r) ;
        if(dl <= jl) ask(a[p].l) ;
    }
}
int main(){
    L t;
    scanf("%lld",&t);
    while(t-- ) {
        scanf("%lld%lld",&n,&m) ;
        for(L i=1;i<=n;i++){
            for(L k=0;k<3;k++)scanf("%lld",&a[i].d[k]) ;
            a[i].l = a[i].r = 0 ;
            a[i].id = i ;
        }
        root = build(1,n,0);
        for(L i=1;i<=m;i++){
            scanf("%lld%lld%lld",&x,&y,&z) ;
            jl = INF ;
            ans = -1 ;
            ask(root);
            printf("%lld %lld %lld\n",a[ans].d[0],a[ans].d[1],a[ans].d[2]) ;
        }
    }
}
