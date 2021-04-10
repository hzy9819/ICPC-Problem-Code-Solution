x = input().split()
l = int(x[0])
r = int(x[1])
a = int(x[2])

if l > r :
    l, r = r, l

temp = r - l

if temp <= a :
    a -= temp;
    ans = r + (a // 2)
else :
    ans = l + a

print(ans * 2)
