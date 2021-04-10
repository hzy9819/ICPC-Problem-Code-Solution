#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct Edge{
  int u, v, w;
  Edge(){}
  Edge(int _u, int _v, int _w):u{_u}, v{_v}, w{_w}{}
  int other(int x){
    return x ^ u ^ v;
  }
};
vector<int> adj[4];
int comp[4];
Edge e[101];
bool done[101];
int com = 1;
int mn = 1e9;
int solve(int u, int com){
  comp[u] = com;
  int ans = 0;
  for(auto el : adj[u])
    if(!done[el]){
      done[el] = 1;
      ans += solve(e[el].other(u), com) + e[el].w;
      if((adj[e[el].v].size() & 1) && (adj[e[el].u].size() & 1) && e[el].u != e[el].v)
        mn = min(mn, e[el].w);
    }
  return ans;
}
int main() {
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
  int n;
  cin >> n;
  int a, b, v;
  for(int i = 0;i < n;i++){
    cin >> a >> v >> b;
    a--, b--;
    adj[a].push_back(i);
    adj[b].push_back(i);
    e[i] = Edge(a, b, v);
  }
  int ans = 0;
  for(int i = 0;i < 4;i++){
    if(comp[i] == 0){
      mn = 1e9;
      int res = solve(i, com++);
      int odd = 0;
      for(int j = 0;j < 4;j++){
        if(comp[j] == com - 1 && (adj[j].size() & 1))
          odd++;
      }
      if(odd == 4){
        res -= mn;
      }
      ans = max(ans, res);
    }
  }
  cout << ans;
}
