# 改寫自官方 Chapter 13/red_black_tree.py（MIT License）：nil 哨兵＋平鋪函式
RED, BLACK = "R", "B"


class Node:
    def __init__(self, key, color, nil=None):
        self.key = key
        self.color = color
        self.left = self.right = self.p = nil


NIL = Node(None, BLACK)
NIL.left = NIL.right = NIL.p = NIL
T = {"root": NIL}


def left_rotate(x):
    y = x.right                          # y 升上來、β 過繼給 x
    x.right = y.left
    if y.left is not NIL:
        y.left.p = x
    y.p = x.p
    if x.p is NIL:
        T["root"] = y
    elif x is x.p.left:
        x.p.left = y
    else:
        x.p.right = y
    y.left = x
    x.p = y


def right_rotate(x):
    y = x.left
    x.left = y.right
    if y.right is not NIL:
        y.right.p = x
    y.p = x.p
    if x.p is NIL:
        T["root"] = y
    elif x is x.p.right:
        x.p.right = y
    else:
        x.p.left = y
    y.right = x
    x.p = y


def rb_insert(k):
    z = Node(k, RED, NIL)                # 新節點永遠先塗紅
    y, x = NIL, T["root"]
    while x is not NIL:
        y = x
        x = x.left if k < x.key else x.right
    z.p = y
    if y is NIL:
        T["root"] = z
    elif k < y.key:
        y.left = z
    else:
        y.right = z
    rb_insert_fixup(z)


def rb_insert_fixup(z):
    while z.p.color == RED:
        left = z.p is z.p.p.left
        y = z.p.p.right if left else z.p.p.left      # 叔叔
        if y.color == RED:                           # Case 1：叔紅 → 變色上推
            z.p.color = y.color = BLACK
            z.p.p.color = RED
            z = z.p.p
        else:
            if z is (z.p.right if left else z.p.left):   # Case 2：內側 → 轉外側
                z = z.p
                (left_rotate if left else right_rotate)(z)
            z.p.color = BLACK                        # Case 3：變色＋旋轉收工
            z.p.p.color = RED
            (right_rotate if left else left_rotate)(z.p.p)
    T["root"].color = BLACK


def inorder(x, out):
    if x is not NIL:
        inorder(x.left, out)
        out.append("%d%s" % (x.key, x.color))
        inorder(x.right, out)


def black_height(x):                     # 驗證性質④⑤：違規回 -1
    if x is NIL:
        return 1
    if x.color == RED and (x.left.color == RED or x.right.color == RED):
        return -1
    hl, hr = black_height(x.left), black_height(x.right)
    return -1 if (hl < 0 or hl != hr) else hl + (x.color == BLACK)


for k in [41, 38, 31, 12, 19, 8]:
    rb_insert(k)
out = []
inorder(T["root"], out)
print(" ".join(out))
print("root =", T["root"].key, ", 黑高度 =", black_height(T["root"]))
