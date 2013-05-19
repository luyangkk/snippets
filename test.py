import sys

def f(n, k):
  r = 0
  for i in xrange(2, n + 1):
    r = (r + k) % i
  return r

def josephus(n, k):
  if n == 1:
    return 0
  else:
    return (k + josephus(n - 1, k)) % n;

print josephus(int(sys.argv[1]), int(sys.argv[2]))
print f(int(sys.argv[1]), int(sys.argv[2]))
