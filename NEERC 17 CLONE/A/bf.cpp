#include <bits/stdc++.h>
using namespace std;
const int maxn=200003;
int n;
struct query{
    int typ, x, y, id;
}que[maxn];
int x[maxn];
int my[maxn<<2];
int id[maxn<<2];
void pushup(int u){
    my[u]=max(my[2*u], my[2*u+1]);
}
void build(int u, int l, int r){
    my[u]=0;
    if(l==r){
        return;
    }
    int mid=(l+r)/2;
    build(2*u, l, mid);
    build(2*u+1, mid+1, r);
}
void update(int u, int pos, int l, int r, int i){
    if(pos>r||pos<l)return;
    if(l==r){
        id[u]=i;
        my[u]=que[i].y;
        return ;
    }
    int mid=(l+r)/2;
    update(2*u, pos, l, mid, i);
    update(2*u+1, pos, mid+1, r, i);
    pushup(u);
}
int Ql(int u, int ql, int qr, int l, int r, int i){
    if(qr<l||ql>r||my[u]*2<=que[i].y)return 0;
    if(l==r){
        if(1ll*(que[id[u]].x-que[i].x)*(que[id[u]].x-que[i].x)+1ll*(que[id[u]].y-que[i].y)*(que[id[u]].y-que[i].y)<1ll*que[id[u]].y*que[id[u]].y){
            printf("%d\n", id[u]);
            id[u]=0;
            my[u]=0;
            return 1;
        }
        return -1;
    }
    int mid=(l+r)/2;
    int ret1=Ql(2*u+1, ql, qr, mid+1, r, i);
    int ret=0;
    if(ret1==1)ret=1;
    else if(ret1==-1)ret=-1;
    else ret=Ql(2*u, ql, qr, l, mid, i);
    pushup(u);
    return ret;
}
int Qr(int u, int ql, int qr, int l, int r, int i){
    if(qr<l||ql>r||my[u]*2<=que[i].y)return 0;
    if(l==r){
        if(1ll*(que[id[u]].x-que[i].x)*(que[id[u]].x-que[i].x)+1ll*(que[id[u]].y-que[i].y)*(que[id[u]].y-que[i].y)<1ll*que[id[u]].y*que[id[u]].y){
            printf("%d\n", id[u]);
            id[u]=0;
            my[u]=0;
            return 1;
        }
        return -1;
    }
    int mid=(l+r)/2;
    int ret1=Qr(2*u, ql, qr, l, mid, i);
    int ret=0;
    if(ret1==1)ret=1;
    else if(ret1==-1)ret=-1;
    else ret=Qr(2*u+1, ql, qr, mid+1, r, i);
    pushup(u);
    return ret;
}
int main(){
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d", &que[i].typ, &que[i].x, &que[i].y);
        que[i].id=i;
        x[i]=que[i].x;
    }
    sort(x+1, x+1+n);
    build(1, 1, n);
    for(int i=1;i<=n;i++){
        if(que[i].typ==1){
            int pos=lower_bound(x+1, x+1+n, que[i].x)-x;
            update(1, pos, 1, n, i);
        }
        else {
            int pos=lower_bound(x+1, x+1+n, que[i].x)-x;
            if(Ql(1, 1, pos, 1, n, i)!=1&&Qr(1, pos, n, 1, n, i)!=1){
                printf("-1\n");
            }
        }
    }
}
