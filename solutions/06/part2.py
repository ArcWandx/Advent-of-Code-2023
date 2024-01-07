n = 313109012141201
k = 53897698

a = 0
b = k - a
while(a * b < n):
    a += 1
    b = k - a

print(b - a + 1)
