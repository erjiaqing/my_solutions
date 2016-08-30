mod = 10 ** 6 + 3

def powmod(n, k):
    ret = 1
    while k > 0:
        if k % 2 == 1:
            ret = ret * n % mod
        n = n * n % mod
        k = int(k / 2);
    return ret

def sol():
    n, k = raw_input().split(' ')
    n = int(n)
    k = int(k)
    if n < 63 and 2 ** n < k:
        print("1 1")
        return 0
    bpow = n * (k - 1)
    lastpow = 0
    for i in range(1, 63):
        if k > 2 ** i:
            bpow = bpow - (k - 1) / (2 ** i)
            lastpow = lastpow + (k - 1) / (2 ** i)
    b = powmod(2, bpow)
    if k > mod:
        print("%d %d"%(b, b))
        return 0
    tb = powmod(2, n)
    a = 1
    for i in range(1, k):
        a = a * (tb - i) % mod
    a = (powmod(2, n * (k - 1)) + mod - a) % mod
    a = a * powmod(powmod(2, lastpow), mod - 2) % mod
    print("%d %d"%(a, b))

sol()
