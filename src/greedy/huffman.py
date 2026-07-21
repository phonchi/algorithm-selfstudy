# Huffman 編碼（改寫自官方 Chapter 15/huffman.py 精簡成 heapq 平鋪版，MIT License）
import heapq

freq = {"a": 45, "b": 13, "c": 12, "d": 16, "e": 9, "f": 5}   # CLRS 圖 15.5

# heap 元素 (頻率, 序號, 節點)；序號避免頻率平手時比較 dict
counter = 0
h = []
for ch, fr in sorted(freq.items()):
    h.append((fr, counter, {"ch": ch}))
    counter += 1
heapq.heapify(h)

while len(h) > 1:                       # n−1 次合併
    f1, _, x = heapq.heappop(h)         # 頻率最小
    f2, _, y = heapq.heappop(h)         # 次小
    counter += 1
    heapq.heappush(h, (f1 + f2, counter, {"left": x, "right": y}))

root = h[0][2]
codes = {}


def walk(node, code):                   # 左 0 右 1 走到葉
    if "ch" in node:
        codes[node["ch"]] = code or "0"
        return
    walk(node["left"], code + "0")
    walk(node["right"], code + "1")


walk(root, "")
print("codes:", dict(sorted(codes.items())))
print("期望編碼長度:", sum(freq[c] * len(codes[c]) for c in freq))
