#Problem D - Codeforces round 251 Div.2

## A beautiful solution by @goovie

Sort array a in asc and b in desc

Then ans=∑(b[i]-a[i]) (where b[i] is bigger than a[i])

Why it is right?

Suppose all elements in array b is less than X and all elements in array a is bigger than X

then we get -> ans += X-a[i]+(b[i]-X) => b[i]-a[i]

Soooooo beautiful!
