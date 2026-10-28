from itertools import product

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

def formula(n, a, k):
    b = sorted(a)
    S = sum(b)
    O = min(n, k)
    if O % 2 != k % 2:
        O -= 1
    # c0
    if O == 0:
        c0 = b[0] if n > 0 else 0
    else:
        pmin = min(b[j] - j for j in range(O))
        m_odd = pmin + k
        if O < n:
            c0 = min(b[O], m_odd)
        else:
            c0 = m_odd
    T = S + O * k - O * (O - 1) // 2 - (k - O) // 2
    V = T // n  # floor division
    return min(c0, V)

mismatch = 0
for n in (1, 2, 3):
    arange = range(0, 6) if n <= 2 else range(0, 4)
    for a in product(arange, repeat=n):
        for k in range(0, 13):
            bb = brute(n, list(a), k)
            ff = formula(n, list(a), k)
            if bb != ff:
                print(f"MISMATCH n={n} a={a} k={k} brute={bb} formula={ff}")
                mismatch += 1
                if mismatch > 40:
                    raise SystemExit
print("done, mismatches =", mismatch)

# some bigger k checks vs full model (model matched brute earlier)
def model(n, a, k):
    b = sorted(a)
    best = None
    for O in range(0, min(n, k)+1):
        if O % 2 != k % 2:
            continue
        ceilings = []
        for j in range(O):
            ceilings.append(b[j] + (k - j))
        for j in range(O, n):
            ceilings.append(b[j])
        c = sorted(ceilings)
        D = (k - O) // 2
        V = min(c[0], (sum(c) - D) // n)
        if best is None or V > best:
            best = V
    return best

for n in (1,2,3,4,5):
    for a in product(range(0,4), repeat=n):
        for k in range(0, 20):
            mm = model(n, list(a), k)
            ff = formula(n, list(a), k)
            if mm != ff:
                print(f"MISMATCH2 n={n} a={a} k={k} model={mm} formula={ff}")
                raise SystemExit
print("formula == model for larger n,k: OK")