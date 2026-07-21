# 開放定址（改寫自官方 Chapter 11/open_address_hashtable.py，MIT License）：攤平版
M = 11
EMPTY, DELETED = None, "DEL"


def probe(k, i, use_double):
    h1, h2 = k % M, (1 + k % (M - 1)) if use_double else 1
    return (h1 + i * h2) % M            # linear：步距 1；double：步距 h2(k)


def oa_insert(T, k, use_double):
    for i in range(M):                  # 沿探測序列找第一個可用格
        s = probe(k, i, use_double)
        if T[s] is EMPTY or T[s] == DELETED:
            T[s] = k
            return i + 1                # 回傳探測次數
    raise RuntimeError("hash table overflow")


def oa_search(T, k, use_double):
    for i in range(M):
        s = probe(k, i, use_double)
        if T[s] == k:
            return s
        if T[s] is EMPTY:               # 空格 = 確定不在；DELETED 要繼續走
            return None
    return None


keys = [10, 22, 31, 4, 15, 28, 17, 88, 59]
for use_double in (False, True):
    T = [EMPTY] * M
    probes = sum(oa_insert(T, k, use_double) for k in keys)
    name = "double hashing" if use_double else "linear probing"
    print("%s：表 = %s｜總探測 %d 次" %
          (name, " ".join("·" if v is EMPTY else str(v) for v in T), probes))
