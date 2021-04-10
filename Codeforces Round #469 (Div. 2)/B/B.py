rd = input().split()
n = int(rd[0])
m = int(rd[1])

x = input().split()
y = input().split()

j = 0
ctx = 0; cty = 0
ans = 0
for i in range(0, n) :
    ctx += int(x[i])
    while (cty < ctx) & (j < m) :
        cty += int(y[j])
        j += 1
    if ctx == cty :
        ans += 1
        ctx = 0
        cty = 0

print(ans)
