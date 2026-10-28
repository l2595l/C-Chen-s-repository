import random, subprocess, sys

def formula(n, a, k):
    b = sorted(a)
    S = sum(b)
    O = min(n, k)
    if O % 2 != k % 2:
        O -= 1
    if O == 0:
        c0 = b[0]
    else:
        pmin = min(b[j] - j for j in range(O))
        m_odd = pmin + k
        if O < n:
            c0 = min(b[O], m_odd)
        else:
            c0 = m_odd
    T = S + O * k - O * (O - 1) // 2 - (k - O) // 2
    V = T // n
    return min(c0, V)

random.seed(12345)
EXE = "D:/IT_Program/Data/暑假做题/23ak/J.exe"

for trial in range(300):
    n = random.randint(1, 8)
    a = [random.randint(0, 10) for _ in range(n)]
    q = random.randint(1, 30)
    ks = []
    for _ in range(q):
        r = random.random()
        if r < 0.3:
            ks.append(random.randint(0, 30))
        elif r < 0.6:
            ks.append(random.randint(0, 100000))
        else:
            ks.append(random.randint(0, 10**9))
    inp = f"{n} {q}\n" + " ".join(map(str, a)) + "\n" + " ".join(map(str, ks)) + "\n"
    out = subprocess.run([EXE], input=inp, capture_output=True, text=True).stdout.split()
    if len(out) != q:
        print("BAD OUTPUT LEN", trial, inp, out); sys.exit(1)
    got = list(map(int, out))
    exp = [formula(n, a, k) for k in ks]
    if got != exp:
        print("MISMATCH trial", trial)
        print("n=", n, "a=", a)
        for k, g, e in zip(ks, got, exp):
            if g != e:
                print("  k=", k, "got", g, "exp", e)
        sys.exit(1)
print("all", trial+1, "random trials OK")