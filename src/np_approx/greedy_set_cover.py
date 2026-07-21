# 貪婪集合覆蓋（改寫自官方 Chapter 35/greedy_set_cover.py，MIT License）
# CLRS 圖 35.3 的例子：12 個元素、6 個集合；貪婪選 4 個、最佳 3 個
X = set(range(1, 13))
F = {"S1": {1, 2, 3, 4, 5, 6}, "S2": {5, 6, 8, 9}, "S3": {1, 4, 7, 10},
     "S4": {2, 5, 7, 8, 11}, "S5": {3, 6, 9, 12}, "S6": {10, 11}}

U = set(X)                                  # 尚未被蓋住的元素
cover = []
while U:
    best = max(F, key=lambda s: len(F[s] & U))      # 蓋最多新元素的集合
    got = F[best] & U
    U -= F[best]
    cover.append(best)
    print("選 %s（新蓋 %d 個：%s），剩 %d 個未蓋" %
          (best, len(got), sorted(got), len(U)))
print("貪婪覆蓋：", cover, "共", len(cover), "個（最佳 {S3,S4,S5} 只要 3 個）")
