n = 313109012141201
k = 53897698

#  s = 6000000 # approx sqrt(n)
s = 0
while(s * (k-s) < n):
    s += 1

print(s)
print((k-s) - s + 1)
