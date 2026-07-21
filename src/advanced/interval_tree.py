# 區間樹（改寫自官方 Chapter 17/interval_tree.py 精簡，MIT License）
class Node:
    def __init__(self, lo, hi):
        self.lo, self.hi, self.mx = lo, hi, hi
        self.l = self.r = None


def insert(x, lo, hi):
    if x is None:
        return Node(lo, hi)
    if lo < x.lo:
        x.l = insert(x.l, lo, hi)
    else:
        x.r = insert(x.r, lo, hi)
    x.mx = max(x.mx, hi)                    # 沿路維護 max（只依自己與孩子）
    return x


def interval_search(x, lo, hi):
    while x is not None and (x.hi < lo or hi < x.lo):   # 不重疊才繼續
        if x.l is not None and x.l.mx >= lo:
            x = x.l                          # 左子樹的 max 夠大 → 解只可能在左
        else:
            x = x.r
    return x


root = None
for a, b in [(16,21),(8,9),(25,30),(5,8),(15,23),
             (17,19),(26,26),(0,3),(6,10),(19,20)]:     # CLRS 圖 17.4
    root = insert(root, a, b)

for a, b in [(22, 25), (11, 14)]:
    hit = interval_search(root, a, b)
    print("SEARCH([%d,%d]) =" % (a, b),
          "[%d,%d]" % (hit.lo, hit.hi) if hit else "NIL（無重疊區間）")
