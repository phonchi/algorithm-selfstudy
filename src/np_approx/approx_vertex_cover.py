# 2-近似 vertex cover（改寫自官方 Chapter 35/approx_vertex_cover.py，MIT License）
E = [("a","b"),("b","c"),("c","d"),("c","e"),("d","e"),("d","f"),("d","g"),("e","f")]

C = set()
alive = list(E)                             # 還沒被蓋住的邊
while alive:
    u, v = alive[0]                         # 任取一條活邊
    C.update([u, v])                        # 兩端點都收
    alive = [e for e in alive if u not in e and v not in e]   # 刪鄰邊
    print("選邊 (%s, %s)，剩 %d 條邊未蓋" % (u, v, len(alive)))
print("cover =", sorted(C), "，|C| =", len(C), "（最佳解 {b,d,e} 只要 3）")
