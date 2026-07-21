# weighted-majority（CLRS §33.2）：三位專家、12 天、錯了砍半——逐輪權重全記錄
experts = {                                  # 每天的 0/1 預測
    "E1": [1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
    "E2": [0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1],
    "E3": [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
}
outcome = [1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1]      # 事後才揭曉

w = {e: 1.0 for e in experts}
my_mistakes = 0
expert_mistakes = {e: 0 for e in experts}
print("day  預測(加權)  結果  權重(E1,E2,E3)")
for day in range(12):
    vote1 = sum(w[e] for e in experts if experts[e][day] == 1)
    vote0 = sum(w[e] for e in experts if experts[e][day] == 0)
    guess = 1 if vote1 >= vote0 else 0               # 加權多數決
    if guess != outcome[day]:
        my_mistakes += 1
    for e in experts:                                # 錯的專家權重砍半
        if experts[e][day] != outcome[day]:
            w[e] /= 2
            expert_mistakes[e] += 1
    print("%3d      %d       %d    (%.4g, %.4g, %.4g)" %
          (day + 1, guess, outcome[day], w["E1"], w["E2"], w["E3"]))

best = min(expert_mistakes.values())
print("我的錯誤 =", my_mistakes, "；各專家錯誤 =", expert_mistakes)
import math
print("上界 2.41·m* + 2.41·lg N = %.2f（m* = %d, N = 3）"
      % (2.41 * best + 2.41 * math.log2(3), best))
