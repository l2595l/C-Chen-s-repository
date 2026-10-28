import sys
from functools import lru_cache
from itertools import product

# brute force max min
def brute(n, a, k):
    best = [None]
    def rec(i, val, col):
        if i == k+1:
            mn = min(val)
            if best[0] is None or mn > best[0]:
                best[0] = mn
            return
        for c in range(n):
            nv = list(val); nc = list(col)
            if col[c] == 0:
                nv[c] += i; nc[c] = 1
            else:
                nv[c] -= i; nc[c] = 0
            rec(i+1, tuple(nv), tuple(nc))
    rec(1, tuple(a), (0,)*n)
    return best[0]

def model(n, a, k):
    b = sorted(a)
    best = None
    # O = number of odd cards
    for O in range(0, min(n, k)+1):
        if O % 2 != k % 2:
            continue
        ceilings = []
        # smallest O get largest final+ times k, k-1, ..., k-O+1
        for j in range(O):
            ceilings.append(b[j] + (k - j))
        for j in range(O, n):
            ceilings.append(b[j])
        c = sorted(ceilings)
        D = (k - O) // 2
        s = sum(c)
        # V = min(c[0], floor((s - D)/n))
        # floor division for possibly negative numerator
        V = (s - D) // n
        V = min(c[0], V)
        if best is None or V > best:
            best = V
    return best

# compare over grid
def test():
    mismatches = 0
    for n in (1,2,3):
        # all a in 0..5 (n=3 -> 0..3 to limit size)
        arange = range(0, 6) if n <= 2 else range(0, 4)
        for a in product(arange, repeat=n):
            for k in range(0, 13):
                if n == 3 and k > 12:
                    continue
                b_ = brute(n, list(a), k)
                m_ = model(n, list(a), k)
                if b_ != m_:
                    print(f"MISMATCH n={n} a={a} k={k} brute={b_} model={m_}")
                    mismatches += 1
                    if mismatches > 40:
                        return
    print("done, mismatches =", mismatches)

test()
