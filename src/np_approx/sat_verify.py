# NP 驗證器示範：3-CNF 證書檢查（線性時間）
clauses = [(1, -2, 3), (-1, 2, 4), (-3, -4, 2)]
x = {1: True, 2: True, 3: False, 4: False}          # 證書（賦值）

for cl in clauses:
    sat = any((lit > 0) == x[abs(lit)] for lit in cl)
    print("子句", cl, "=", sat)
print("驗證結果：", all(any((lit > 0) == x[abs(lit)] for lit in cl)
                       for cl in clauses))
