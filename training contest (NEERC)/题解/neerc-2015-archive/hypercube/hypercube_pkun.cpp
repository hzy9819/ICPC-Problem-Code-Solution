#include <vector>
#include <set>
#include <cassert>
#include <cstdio>

using namespace std;

#define TASKNAME "hypercube"

char c[8][8][8];
int used[8][8][8];
int n, m, h;

set<int> s;

const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0,  0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

bool check(int i, int j, int k) {
    if (!(0 <= i && i < h)) return false;
    if (!(0 <= j && j < n)) return false;
    if (!(0 <= k && k < m)) return false;
    return c[i][j][k] == 'x' && !used[i][j][k];
}

void go(int i, int j, int k, vector<int> b) {
    used[i][j][k] = 1;
    s.insert(b[3]);
    for (int dir = 0; dir < 6; dir++) {
        int ni = i + dx[dir];
        int nj = j + dy[dir];
        int nk = k + dz[dir];
        if (!check(ni, nj, nk)) continue;
        vector<int> nb = b;
        int id = dir / 2;
        swap(nb[id], nb[3]);
        nb[3] *= (dx[dir] + dy[dir] + dz[dir]);
        nb[id] *= -(dx[dir] + dy[dir] + dz[dir]);
        go(ni, nj, nk, nb);
    }
}

int main() {
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
    scanf("%d%d%d", &m, &n, &h);
    int anyx = -1, anyy = -1, anyz = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                scanf(" %c", &c[i][j][k]);
                if (c[i][j][k] == 'x') {
                    anyx = i;
                    anyy = j;
                    anyz = k;
                }
            }
        }
    }
    assert(anyx != -1);
    go(anyx, anyy, anyz, {1, 2, 3, 4});
    if (s.size() == 8) {
        printf("Yes\n");
        return 0;
    } else {
        printf("No\n");
        return 0;
    }
}