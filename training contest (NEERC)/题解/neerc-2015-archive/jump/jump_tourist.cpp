#include <cstdio>
#include <cstdlib>

using namespace std;

#define FILENAME "jump"

const int N = 123456;

int a[N];
int b[N];
int n;

int query() {
  for (int i = 0; i < n; i++) {
    putchar('0' + a[i]);
  }
  printf("\n");
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res;
}

int main() {
  scanf("%d", &n);
  srand(8753);
  while (true) {
    for (int i = 0; i < n; i++) {
      a[i] = rand() % 2;
    }
    int res = query();
    if (res == n / 2) {
      break;
    }
  }
  b[0] = 0;
  for (int j = 1; j < n; j++) {
    a[0] ^= 1;
    a[j] ^= 1;
    int res = query();
    b[j] = (res == n / 2 ? 1 : 0);
    a[0] ^= 1;
    a[j] ^= 1;
  }
  for (int i = 0; i < n; i++) {
    a[i] ^= b[i];
  }
  query();
  for (int i = 0; i < n; i++) {
    a[i] = 1 - a[i];
  }
  query();
  return 0;
}
