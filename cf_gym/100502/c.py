c = [1, 1]
for i in range(2, 10005):
    c.append(c[i - 1] * i)
n = int(raw_input())
n = n + 1
print c[2 * n] / c[n] / c[n] / (n + 1)
